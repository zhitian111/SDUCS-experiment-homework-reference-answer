import stanfordcorenlp
from stanfordcorenlp import StanfordCoreNLP
nlp = StanfordCoreNLP(r'./temp/', lang='zh')
# coding=utf-8
sentence = """央视315晚会曝光湖北省知名的神丹牌、莲田牌“土鸡蛋”实为普通鸡蛋冒充，同时在商标上玩猫腻，分别注
册“鲜土”、注册“好土”商标，让消费者误以为是“土鸡蛋”。3月15日晚间，新京报记者就此事致电湖北神
丹健康食品有限公司方面，其工作人员表示不知情，需要了解清楚情况，截至发稿暂未取得最新回应。新京
报记者还查询发现，湖北神丹健康食品有限公司为农业产业化国家重点龙头企业、高新技术企业，此前曾因
涉嫌虚假宣传“中国最大的蛋品企业”而被罚6万元。"""
print(nlp.word_tokenize(sentence))
print(nlp.pos_tag(sentence))
print(nlp.ner(sentence))
print(nlp.parse(sentence))
print(nlp.dependency_parse(sentence))