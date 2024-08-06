import torch
from tool.darknet2pytorch import Darknet

PATH = "./divot_detection.pth"
divot_detector = Darknet("DivotTest/yolov4.cfg")
divot_detector.load_weights("DivotTest/yolov4.weights")

# print(divot_detector)
torch.save(divot_detector.state_dict(), PATH)
