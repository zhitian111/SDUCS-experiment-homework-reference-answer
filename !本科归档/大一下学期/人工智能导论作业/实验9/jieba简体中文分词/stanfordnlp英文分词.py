import stanfordcorenlp
from stanfordcorenlp import StanfordCoreNLP
nlp = StanfordCoreNLP(r'./temp/', lang='en')
# coding=utf-8
sentence = """Trump was born and raised in the New York City borough of Queens and received
an economics degree from the Wharton School. He was appointed president of
his family's real estate business in 1971, renamed it The Trump Organization,
and expanded it from Queens and Brooklyn into Manhattan. The company built or
renovated skyscrapers, hotels, casinos, and golf courses. Trump later started
various side ventures, including licensing his name for real estate and
consumer products. He managed the company until his 2017 inauguration. He coauthored several books, including The Art of the Deal. He owned the Miss
Universe and Miss USA beauty pageants from 1996 to 2015, and he produced and
hosted The Apprentice, a reality television show, from 2003 to 2015. Forbes
estimates his net worth to be $3.1 billion."""
print(nlp.word_tokenize(sentence))
print(nlp.pos_tag(sentence))
print(nlp.ner(sentence))
print(nlp.parse(sentence))
print(nlp.dependency_parse(sentence))