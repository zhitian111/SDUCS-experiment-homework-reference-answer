# Minimal Extractor base for vendored LightGlue SuperPoint (CVG/LightGlue, Apache-2.0).
from types import SimpleNamespace

import torch


class Extractor(torch.nn.Module):
    default_conf: dict = {}
    preprocess_conf: dict = {}

    def __init__(self, **conf) -> None:
        super().__init__()
        self.conf = SimpleNamespace(**{**self.default_conf, **conf})

