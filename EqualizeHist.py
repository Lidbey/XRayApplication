from skimage.exposure import equalize_hist
import sys
from skimage import io

imgPath = sys.argv[1]
img = io.imread(sys.argv[1])
newImg = equalize_hist(img, 16)

io.imsave('./PythonImage.jpg', newImg)