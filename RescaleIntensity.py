from skimage.exposure import rescale_intensity
import sys
from skimage import io

imgPath = sys.argv[1]
img = io.imread(sys.argv[1])
newImg = rescale_intensity(img)

io.imsave('./PythonImage.jpg', newImg)