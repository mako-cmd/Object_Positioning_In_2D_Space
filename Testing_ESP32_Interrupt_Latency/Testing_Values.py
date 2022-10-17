import numpy
import pandas as pd

#Get csv files

from_mic_1 = pd.read_csv (r'Results/From_Mic_1.csv')
from_mic_2 = pd.read_csv (r'Results/From_Mic_2.csv')
from_mic_3 = pd.read_csv (r'Results/From_Mic_3.csv')
from_centre = pd.read_csv (r'Results/From_Centre.csv')
from_corner = pd.read_csv (r'Results/From_Corner.csv')

#calculate for mic 1 test
mic_1 = from_mic_1.at[5,"Mic_1"]   
mic_2 = from_mic_1.at[5,"Mic_2"]
mic_3 = from_mic_1.at[5,"Mic_3"]
