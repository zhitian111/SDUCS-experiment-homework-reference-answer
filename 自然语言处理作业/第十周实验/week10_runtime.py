# -*- coding: utf-8 -*-
import sys
from pathlib import Path

_root = Path(__file__).resolve().parent.parent
if str(_root) not in sys.path:
    sys.path.insert(0, str(_root))
from nlp_runtime import *  # noqa: F403
