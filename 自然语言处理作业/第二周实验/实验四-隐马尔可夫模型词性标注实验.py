
exp_2_2_test_sentences = [
"我 学习 NLP",
"人工智能 发展 很 快"
]

def load_exp_2_2_data():
    with open("./exp-2.2-data.txt") as f:
        lines = f.readlines()
    return lines
def get_prob(count_dict):
    total = sum(count_dict.values())
    prob = {}
    for key, cnt in count_dict.items():
        prob[key] = (cnt + 1) / (total + len(count_dict))
    return prob
class HMMModel(object):
    def __init__(self):
        pass
    def train_HMM(self, train_data):
        sentences = []
        for line in train_data:
            words_tags = []
            for item in line.split():
                word, tag = item.split("/")
                words_tags.append((word, tag))
            sentences.append(words_tags)
        from collections import defaultdict
        # 初始化三个字典
        pi = defaultdict(int)  # 初始概率
        A = defaultdict(lambda: defaultdict(int))  # 转移概率
        B = defaultdict(lambda: defaultdict(int))  # 发射概率

        for sent in sentences:
            # 1. 统计句首词性 π
            first_word, first_tag = sent[0]
            pi[first_tag] += 1

            # 2. 统计转移 A 和发射 B
            for i in range(len(sent)):
                word, tag = sent[i]
                B[tag][word] += 1  # 发射：tag → word

                # 如果不是最后一个词，统计转移
                if i < len(sent) - 1:
                    next_tag = sent[i + 1][1]
                    A[tag][next_tag] += 1
        # 转概率
        pi_prob = get_prob(pi)
        A_prob = {t: get_prob(A[t]) for t in A}
        B_prob = {t: get_prob(B[t]) for t in B}

        self.pi_prob = pi_prob
        self.A_prob = A_prob
        self.B_prob = B_prob
        self.pi = pi
        self.A = A
        self.B = B

    def viterbi(self, words):
        all_tags = ['r', 'v', 'n', 'p', 'd', 'a']
        n = len(words)

        V = [{}]
        path = {}

        for tag in all_tags:
            p = self.pi_prob.get(tag, 1e-5) * self.B_prob[tag].get(words[0], 1e-5)
            V[0][tag] = p
            path[tag] = [tag]

        for t in range(1, n):
            V.append({})
            new_path = {}

            for curr_tag in all_tags:
                max_p = 0
                best_prev = ''

                for prev_tag in V[t - 1]:
                    trans_p = self.A_prob.get(prev_tag, {}).get(curr_tag, 1e-5)
                    emit_p = self.B_prob.get(curr_tag, {}).get(words[t], 1e-5)
                    prob = V[t-1][prev_tag] * trans_p * emit_p

                    if prob > max_p:
                        max_p = prob
                        best_prev = prev_tag

                V[t][curr_tag] = max_p
                new_path[curr_tag] = path[best_prev] + [curr_tag]

            path = new_path

        max_prob, best_tag = max([(V[-1][tag], tag) for tag in V[-1]])
        return path[best_tag]
if __name__ == '__main__':
    HMM = HMMModel()
    HMM.train_HMM(load_exp_2_2_data())
    result = [f"原句：{i}\n结果：{HMM.viterbi(i.split())}" for i in exp_2_2_test_sentences]
    for item in result:
        print(item)