import json
import torch
import numpy as np
from ultralytics import YOLO

@torch.no_grad()
def init():
    """Initialize model
        Returns: model
    """
    model = YOLO('/project/train/models/yolo11m/train2/weights/best.pt')
    return model


def process_image(handle=None, input_image=None, args=None, **kwargs):
    """Do inference to analysis input_image and get output
        Arguments:
            handle: algorithm handle returned by init()

            input_image (numpy.ndarray): image to be process, format: (h, w, c), BGR

            args: string in JSON format, format: {
                "mask_output_path": "/path/to/output/mask.png"
            }
        Returns: process result
    """
    model = handle
    
    result_dict = {
        "model_data": {
            "objects": []
        }
    }

    results_list = model.predict(input_image, device=0)[0]

    for result_ele in results_list:
        obj_dict = {}
        name = result_ele.names[int(result_ele.boxes.cls)]
        x = int(result_ele.boxes.xywh[0][0])
        y = int(result_ele.boxes.xywh[0][1])
        width = int(result_ele.boxes.xywh[0][2])
        height = int(result_ele.boxes.xywh[0][3])
        x = int(x - width / 2)
        y = int(y - height / 2)
        confidence = float(result_ele.boxes.conf)
        obj_dict["name"] = name
        obj_dict["x"] = x
        obj_dict["y"] = y
        obj_dict["height"] = height
        obj_dict["width"] = width
        obj_dict["confidence"] = confidence
        result_dict["model_data"]["objects"].append(obj_dict)
    return json.dumps(result_dict, indent=4)