import pickle
from skimage.transform import resize
from skimage.io import imread
import sys


model = pickle.load(open('modelLogistic.sav','rb'))
photoPath = sys.argv[1]
photo = imread(photoPath, as_gray = True)
photoResized = resize(photo, (64,64))
photoR = photoResized.reshape(1,64*64)

out = model.predict(photoR)
print(out[0])