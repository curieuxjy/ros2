import torch
from tool.darknet2pytorch import Darknet

PATH = "./checkpoints/yolov4_divot.pth"
divot_detector = Darknet("cfg/yolov4_divot.cfg")
divot_detector.load_weights("checkpoints/yolov4_divot.weights")

# print(divot_detector)
torch.save(divot_detector.state_dict(), PATH)
