from dataclasses import dataclass
from typing import Dict, List, Tuple

import numpy as np
import xml.etree.ElementTree as ET


@dataclass(frozen=True)
class SentencePair:
    """
    Contains lists of tokens (strings) for source and target sentence
    """
    source: List[str]
    target: List[str]


@dataclass(frozen=True)
class TokenizedSentencePair:
    """
    Contains arrays of token vocabulary indices (preferably np.int32) for source and target sentence
    """
    source_tokens: np.ndarray
    target_tokens: np.ndarray


@dataclass(frozen=True)
class LabeledAlignment:
    """
    Contains arrays of alignments (lists of tuples (source_pos, target_pos)) for a given sentence.
    Positions are numbered from 1.
    """
    sure: List[Tuple[int, int]]
    possible: List[Tuple[int, int]]


def extract_sentences(filename: str) -> Tuple[List[SentencePair], List[LabeledAlignment]]:
    """
    Given a file with tokenized parallel sentences and alignments in XML format, return a list of sentence pairs
    and alignments for each sentence.

    Args:
        filename: Name of the file containing XML markup for labeled alignments

    Returns:
        sentence_pairs: list of `SentencePair`s for each sentence in the file
        alignments: list of `LabeledAlignment`s corresponding to these sentences
    """
    sentence_pairs = []
    alignments = []

    with open(filename, 'r') as file:
        data = file.read().replace('&', '&amp;')

    # Начинаем парсить xml-файл
    parser = ET.XMLParser(encoding="utf-8")
    tree = ET.fromstring(data, parser=parser)
    items = tree.findall('s')

    # Пробегаемся по всем парам
    for item in items:
        sentence_pairs.append(SentencePair(item.find('english').text.split(),
                                           item.find('czech').text.split()))

        try:
            sure = [tuple(map(int, lst.split('-'))) for lst in item.find('sure').text.split()]
        except AttributeError:
            sure = []

        try:
            possible = [tuple(map(int, lst.split('-'))) for lst in item.find('possible').text.split()]
        except AttributeError:
            possible = []

        alignments.append(LabeledAlignment(sure, possible))

    return sentence_pairs, alignments


def get_token_to_index(sentence_pairs: List[SentencePair], freq_cutoff=None) -> Tuple[Dict[str, int], Dict[str, int]]:
    """
    Given a parallel corpus, create two dictionaries token->index for source and target language.

    Args:
        sentence_pairs: list of `SentencePair`s for token frequency estimation
        freq_cutoff: if not None, keep only freq_cutoff most frequent tokens in each language

    Returns:
        source_dict: mapping of token to a unique number (from 0 to vocabulary size) for source language
        target_dict: mapping of token to a unique number (from 0 to vocabulary size) target language
    """
    source_dict = {}
    target_dict = {}

    # Frequency estimation
    for pair in sentence_pairs:
        for word in pair.source:
            source_dict[word] = source_dict.get(word, 0) + 1
        for word in pair.target:
            target_dict[word] = target_dict.get(word, 0) + 1

    # Keep only freq_cutoff most frequent tokens
    source_dict = {k: v for k, v in sorted(source_dict.items(), key=lambda item: item[1], reverse=True)[:freq_cutoff]}
    target_dict = {k: v for k, v in sorted(target_dict.items(), key=lambda item: item[1], reverse=True)[:freq_cutoff]}

    # Mapping of token to a unique number
    i, j = (0, 0)

    for key in source_dict.keys():
        source_dict[key] = i
        i += 1

    for key in target_dict.keys():
        target_dict[key] = j
        j += 1

    return source_dict, target_dict


def tokenize_sents(sentence_pairs: List[SentencePair], source_dict, target_dict) -> List[TokenizedSentencePair]:
    """
    Given a parallel corpus and token_to_index for each language, transform each pair of sentences from lists
    of strings to arrays of integers. If either source or target sentence has no tokens that occur in corresponding
    token_to_index, do not include this pair in the result.

    Args:
        sentence_pairs: list of `SentencePair`s for transformation
        source_dict: mapping of token to a unique number for source language
        target_dict: mapping of token to a unique number for target language

    Returns:
        tokenized_sentence_pairs: sentences from sentence_pairs, tokenized using source_dict and target_dict
    """
    tokenized_sentence_pairs = []

    for pair in sentence_pairs:
        source_tokens = np.array([source_dict.get(word) for word in pair.source if word in source_dict.keys()])
        target_tokens = np.array([target_dict.get(word) for word in pair.target if word in target_dict.keys()])
        if len(source_tokens) != 0:
            tokenized_sentence_pairs.append(TokenizedSentencePair(source_tokens, target_tokens))

    return tokenized_sentence_pairs
