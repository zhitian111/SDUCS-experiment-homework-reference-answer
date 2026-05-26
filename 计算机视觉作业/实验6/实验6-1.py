# -*- coding: utf-8 -*-
"""实验6：SIFT / SURF / ORB 检测与匹配。需先运行 实验6-0.py 生成变换图。"""

from pathlib import Path
import time

import cv2
import numpy as np

ROOT = Path(__file__).resolve().parent
FIG_DIR = ROOT / "figures"
IMG1 = ROOT / ".." / "mumu.jpg"
IMG2 = ROOT / "images" / "mumu_random.jpg"


def ratio_test(knn_matches, ratio=0.75):
    good = []
    for pair in knn_matches:
        if len(pair) < 2:
            continue
        m, n = pair[0], pair[1]
        if m.distance < ratio * n.distance:
            good.append(m)
    return good


def draw_keypoints(img_bgr, kps, out_path):
    vis = cv2.drawKeypoints(
        img_bgr,
        kps,
        None,
        flags=cv2.DrawMatchesFlags_DRAW_RICH_KEYPOINTS,
    )
    cv2.imwrite(str(out_path), vis)


def run_one(name, detector, norm, img1_bgr, img2_bgr, prefix: str):
    g1 = cv2.cvtColor(img1_bgr, cv2.COLOR_BGR2GRAY)
    g2 = cv2.cvtColor(img2_bgr, cv2.COLOR_BGR2GRAY)

    t0 = time.perf_counter()
    kp1, des1 = detector.detectAndCompute(g1, None)
    kp2, des2 = detector.detectAndCompute(g2, None)
    t_detect = (time.perf_counter() - t0) * 1000

    if des1 is None or des2 is None or len(kp1) == 0 or len(kp2) == 0:
        print(f"[{name}] 未检测到足够特征")
        return

    draw_keypoints(img1_bgr, kp1, FIG_DIR / f"{prefix}_{name}_kp1.png")
    draw_keypoints(img2_bgr, kp2, FIG_DIR / f"{prefix}_{name}_kp2.png")

    matcher = cv2.BFMatcher(norm)
    t1 = time.perf_counter()
    knn = matcher.knnMatch(des1, des2, k=2)
    good = ratio_test(knn, ratio=0.75)
    t_match = (time.perf_counter() - t1) * 1000

    match_vis = cv2.drawMatches(
        img1_bgr,
        kp1,
        img2_bgr,
        kp2,
        good,
        None,
        matchColor=(0, 255, 0),
        singlePointColor=(255, 0, 0),
        flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS,
    )
    cv2.imwrite(str(FIG_DIR / f"{prefix}_{name}_matches.png"), match_vis)

    if len(good) >= 4:
        pts1 = np.float32([kp1[m.queryIdx].pt for m in good]).reshape(-1, 1, 2)
        pts2 = np.float32([kp2[m.trainIdx].pt for m in good]).reshape(-1, 1, 2)
        _, mask = cv2.findHomography(pts1, pts2, cv2.RANSAC, 5.0)
        if mask is not None:
            inliers = [good[i] for i in range(len(good)) if mask[i]]
            inlier_vis = cv2.drawMatches(
                img1_bgr,
                kp1,
                img2_bgr,
                kp2,
                inliers,
                None,
                matchColor=(0, 255, 255),
                flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS,
            )
            cv2.imwrite(
                str(FIG_DIR / f"{prefix}_{name}_matches_ransac.png"),
                inlier_vis,
            )
            print(
                f"[{name}] kp1={len(kp1)}, kp2={len(kp2)}, "
                f"good={len(good)}, inliers={len(inliers)}, "
                f"detect={t_detect:.1f}ms, match={t_match:.1f}ms"
            )
            return

    print(
        f"[{name}] kp1={len(kp1)}, kp2={len(kp2)}, good={len(good)}, "
        f"detect={t_detect:.1f}ms, match={t_match:.1f}ms"
    )


def build_detectors():
    algos = {
        "SIFT": (cv2.SIFT_create(nfeatures=3000), cv2.NORM_L2),
        "ORB": (cv2.ORB_create(nfeatures=5000), cv2.NORM_HAMMING),
    }
    try:
        surf = cv2.xfeatures2d.SURF_create(hessianThreshold=400)
        algos["SURF"] = (surf, cv2.NORM_L2)
    except Exception as e:
        print("SURF 不可用，跳过:", e)
    return algos


def main():
    FIG_DIR.mkdir(exist_ok=True)

    if not IMG1.exists():
        raise FileNotFoundError(f"找不到原图: {IMG1.resolve()}")
    if not IMG2.exists():
        raise FileNotFoundError(
            f"找不到变换图: {IMG2.resolve()}\n"
            "请先运行: python 实验6-0.py"
        )

    img1 = cv2.imread(str(IMG1))
    img2 = cv2.imread(str(IMG2))
    if img1 is None or img2 is None:
        raise RuntimeError("图像读取失败")

    print(f"图1: {IMG1.resolve()}")
    print(f"图2: {IMG2.resolve()}")

    prefix = "mumu"
    for name, (detector, norm) in build_detectors().items():
        run_one(name, detector, norm, img1, img2, prefix)

    print(f"结果已保存到: {FIG_DIR.resolve()}")


if __name__ == "__main__":
    main()
