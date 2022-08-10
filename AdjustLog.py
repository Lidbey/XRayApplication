from skimage.exposure import adjust_log
import sys
from skimage import io

imgPath = sys.argv[1]
img = io.imread(sys.argv[1])
newImg = adjust_log(img, 1)

io.imsave('./PythonImage.jpg', newImg)