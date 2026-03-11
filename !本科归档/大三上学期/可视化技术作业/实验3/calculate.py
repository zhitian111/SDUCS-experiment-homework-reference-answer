import json
import pandas as pd
from sklearn.datasets import load_iris
from sklearn.decomposition import PCA
from sklearn.manifold import TSNE

# 加载数据
iris = load_iris()
X = iris.data
y = iris.target
target_names = iris.target_names

# PCA 2D
pca_2d = PCA(n_components=2)
X_pca_2d = pca_2d.fit_transform(X)

# PCA 3D
pca_3d = PCA(n_components=3)
X_pca_3d = pca_3d.fit_transform(X)

# t-SNE 2D
tsne_2d = TSNE(n_components=2, random_state=42)
X_tsne_2d = tsne_2d.fit_transform(X)

# t-SNE 3D
tsne_3d = TSNE(n_components=3, random_state=42)
X_tsne_3d = tsne_3d.fit_transform(X)

# 保存数据到JSON
data = {
    "pca_2d": [{"x": float(x[0]), "y": float(x[1]), "label": int(y[i])} for i, x in enumerate(X_pca_2d)],
    "pca_3d": [{"x": float(x[0]), "y": float(x[1]), "z": float(x[2]), "label": int(y[i])} for i, x in enumerate(X_pca_3d)],
    "tsne_2d": [{"x": float(x[0]), "y": float(x[1]), "label": int(y[i])} for i, x in enumerate(X_tsne_2d)],
    "tsne_3d": [{"x": float(x[0]), "y": float(x[1]), "z": float(x[2]), "label": int(y[i])} for i, x in enumerate(X_tsne_3d)],
    "target_names": target_names.tolist()
}

with open("iris_vis.json", "w") as f:
    json.dump(data, f, indent=4)

print("数据保存成功: iris_vis.json")
