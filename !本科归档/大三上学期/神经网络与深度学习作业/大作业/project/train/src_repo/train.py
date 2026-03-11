# train_finetune.py  基于 YOLOv11 预训练权重微调
# 针对小目标检测（无人机视角车辆）优化
from ultralytics import YOLO

model = YOLO('/project/train/src_repo/yolo11s.pt')

model.train(
    data='/project/train/src_repo/data.yaml',               # 数据集配置
    epochs=150,                      # 增加训练轮数（2万张图片需要更多轮次）
    imgsz=1024,                      # 提高分辨率（小目标检测关键：640->1024）
    batch=4,                       # 批次大小，显存不够就调小（如16/32）
    device='0',                     # GPU 编号，'cpu' 或 '0,1,2,3'
    workers=4,                      # 数据加载线程
    
    # 优化器配置
    optimizer='AdamW',              # 微调推荐 AdamW
    lr0=0.0005,                     # 初始学习率（大数据集可适当提高）
    lrf=0.01,                       # 最终 lr = lr0 * lrf
    weight_decay=0.0005,            # 权重衰减，抑制过拟合
    warmup_epochs=5,                # 增加warmup轮数（大数据集需要更充分预热）
    
    # 数据增强策略（针对小目标优化）
    mosaic=0.2,                     # 降低mosaic（小目标时mosaic可能破坏目标完整性）
    mixup=0.1,                      # 降低mixup（小目标时mixup会让目标更难识别）
    copy_paste=0.0,                 # 关闭copy_paste（对小目标不友好）
    hsv_h=0.01,                     # 降低色调变化（保持目标特征）
    hsv_s=0.5,                      # 降低饱和度变化
    hsv_v=0.3,                      # 降低亮度变化
    degrees=5.0,                    # 降低旋转角度（±5度，避免小目标旋转后丢失）
    translate=0.05,                 # 降低平移幅度（±5%，避免小目标移出视野）
    scale=0.5,                      # 缩放增强（保持默认）
    shear=0.0,                      # 关闭剪切（对小目标不友好）
    perspective=0.0,                # 关闭透视变换（保持小目标形状）
    flipud=0.0,                     # 关闭上下翻转（无人机视角通常不需要）
    fliplr=0.5,                     # 保持左右翻转
    close_mosaic=15,                # 最后15轮关闭mosaic，提升精度
    
    # 小目标检测专用配置
    multi_scale=False,               # 启用多尺度训练（对小目标检测很重要）
    # 或者使用固定多尺度
    # imgsz=[640, 768, 896, 1024],  # 多尺度训练（如果multi_scale不支持，用这个）
    
    # 模型配置
    project='/project/train/models/yolo11s',           # 结果保存根目录
    name='train001',                  # 本次实验子目录
    exist_ok=True,                 # 是否覆盖旧目录
    pretrained=True,                # 强制加载预训练骨干
    
    # 早停和验证
    patience=20,                     # 早停耐心值（20轮无提升则停止，大数据集需要更多耐心）
    save_period=1,                  # 每10轮保存一次检查点
    val=True,                       # 启用验证
    plots=True,                     # 生成训练图表
    
    # 其他优化
    amp=True,                       # 自动混合精度训练（加速且节省显存）
    fraction=1.0,                   # 使用全部数据（2万张图片足够）
    profile=False,                  # 性能分析（调试时开启）
    
    # 损失函数权重（可选，YOLOv11可能不支持，但列出供参考）
    # box=7.5,                       # 边界框损失权重
    # cls=0.5,                       # 分类损失权重
    # dfl=1.5,                       # DFL损失权重
)