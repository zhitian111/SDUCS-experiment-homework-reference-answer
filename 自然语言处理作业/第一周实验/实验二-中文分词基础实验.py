import jieba
exp1_2_test_sentences = ["我爱自然语言处理",
                    "研究生命起源",
                    "南京市长江大桥",
                    "乒乓球拍卖完了",
                    "今天天气很好",
                    "小明硕士毕业于中国科学院",]


def load_exp1_2_data(path="./exp-1.2-data.txt"):
    jieba.load_userdict(path)
    dictionary = []
    with open(path, newline='') as file:
        for line in file:
            dictionary.append(line.strip())
    return dictionary
def get_exp1_2_model():
    dictionary = load_exp1_2_data()
    fmm = FMMModel(dictionary)

    return fmm

def test_exp1_2():
    fmm = get_exp1_2_model()
    jieba_result = [jieba.lcut(i) for i in exp1_2_test_sentences]
    print(f"jieba分词结果为：\n{jieba_result}")

    fmm_result = [fmm.lcut(i) for i in exp1_2_test_sentences]
    print(f"fmm分词结果为\n{fmm_result}")

    three_bodies_fmm = FMMModel(load_exp1_2_data("./《现代汉语词典》（第7版）.txt"))
    three_bodies_text = open("./[2006]《三体》.txt").read().replace("\n", "")

    print(f"fmm分词得到的三体I中词语数量为：\n{len(three_bodies_fmm.lcut(three_bodies_text))}")

class FMMModel:
    def __init__(self, dictionary):
        self.dictionary = set(dictionary)
        self.max_len = max([len(i) for i in dictionary])
    def lcut(self, sentence):
        result = []
        i = 0
        while i < len(sentence):
            matched = False
            max_len = min(self.max_len, len(sentence) - i)
            for j in range(max_len, 0, -1):
                candidate = sentence[i:i + j]
                if candidate in self.dictionary:
                    result.append(candidate)
                    matched = True
                    i += j
                    break
            if not matched:
                result.append(sentence[i])
                i += 1

        return result

if __name__ == "__main__":
    test_exp1_2()
