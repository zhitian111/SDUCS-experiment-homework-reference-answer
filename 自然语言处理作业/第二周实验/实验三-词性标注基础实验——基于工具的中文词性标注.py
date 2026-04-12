import jieba.posseg as pseg

pseg.initialize()


def load_exp_2_1_data():
    with open("./exp-2.1-data.txt") as f:
        lines = f.readlines()
    return list(lines)

if __name__ == '__main__':
    lines = load_exp_2_1_data()
    for sentence in lines:
        print(sentence)
        for word, tag in pseg.cut(sentence):
            print(word, tag)
        print()