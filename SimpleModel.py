
import keras
from skimage import io
from skimage.transform import resize
import sys


model = keras.models.load_model('model.h5')

photoPath = sys.argv[1]
photo = io.imread(photoPath, as_gray=True)
photoResized = resize(photo, (300,400))
photoR = photoResized.reshape(1, 300*400)

out = model.predict(photoR)
print(out[0][0])