import warnings
warnings.filterwarnings("ignore")

import os

import logging
logging.basicConfig(level=logging.ERROR)

import pandas as pd
import numpy as np
from tqdm import tqdm
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.decomposition import TruncatedSVD
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import roc_auc_score
from sklearn.model_selection import StratifiedKFold

df_train = pd.read_table("oppo_breeno_round1_data/gaiic_track3_round1_train_20210228.tsv", names=['q1', 'q2', 'label']).fillna("0")
df_test = pd.read_table('oppo_breeno_round1_data/gaiic_track3_round1_testA_20210228.tsv', names=['q1', 'q2']).fillna("0")
label = df_train['label'].values
df = pd.concat([df_train, df_test], ignore_index=True)
df['text'] = df['q1'] + " " + df['q2']

tfidf = TfidfVectorizer(ngram_range=(1, 5))
tfidf_feature = tfidf.fit_transform(df['text'])
svd_feature = TruncatedSVD(n_components=100).fit_transform(tfidf_feature)
train_df = tfidf_feature[:-len(df_test)]
test_df = tfidf_feature[-len(df_test):]

scores = []

nfold = 5
kf = StratifiedKFold(n_splits=nfold, shuffle=True, random_state=2020)

lr_oof = np.zeros((len(df_train), 2))
lr_predictions = np.zeros((len(df_test), 2))

i = 0
for train_index, valid_index in kf.split(train_df, label):
    print("\nFold {}".format(i + 1))
    X_train, label_train = train_df[train_index], label[train_index]
    X_valid, label_valid = train_df[valid_index], label[valid_index]

    model = LogisticRegression(C=1, n_jobs=20)
    model.fit(X_train, label_train)

    lr_oof[valid_index] = model.predict_proba(X_valid,)
    scores.append(roc_auc_score(label_valid, lr_oof[valid_index][:,1]))
    
    lr_predictions += model.predict_proba(test_df) / nfold
    i += 1
    print(scores)
    
print(np.mean(scores))

pd.DataFrame(lr_predictions[:,1]).to_csv("prediction_result/result.csv", index=False, header=False)

