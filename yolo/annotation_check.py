"""Check Image data and BBox Label"""
import os
import cv2

DIR_PATH = os.path.dirname(os.path.realpath(__file__))

# Load image "./data/test(0000).jpg"
img = cv2.imread(os.path.join(DIR_PATH, "data/test(0000).jpg"))

# Load text label "./data/test(0000).txt"
label_file = os.path.join(DIR_PATH, "data/test(0000).txt")
labels = []

with open(label_file, 'r') as file:
    for line in file:
        parts = line.strip().split()
        class_id = int(parts[0])
        bbox = list(map(float, parts[1:]))
        labels.append((class_id, bbox))

# Define colors for the classes
colors = {
    0: (0, 255, 0),  # Green for Divot
    1: (0, 0, 255)   # Red for Not Divot
}

# Show the image with the label
for class_id, bbox in labels:
    x_center, y_center, width, height = bbox
    x_center, y_center, width, height = int(x_center), int(y_center), int(width), int(height)

    # Calculate the top-left corner of the bbox
    x1 = int(x_center - width / 2)
    y1 = int(y_center - height / 2)
    x2 = int(x_center + width / 2)
    y2 = int(y_center + height / 2)

    # Draw the rectangle
    cv2.rectangle(img, (x1, y1), (x2, y2), colors[class_id], 2)

    # Put the label text
    label_text = "Divot" if class_id == 0 else "Not Divot"
    cv2.putText(img, label_text, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, colors[class_id], 2)

# Display the image
cv2.imshow("Image with Labels", img)
cv2.waitKey(0)
cv2.destroyAllWindows()