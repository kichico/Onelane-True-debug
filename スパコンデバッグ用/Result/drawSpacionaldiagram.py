import pandas as pd
import matplotlib.pyplot as plt

File_dist = 'Global1_distributed.dat'
File_Normal='Global1.csv'
df_distributed = pd.read_csv(File_dist)
df_fixed=pd.read_csv(File_Normal)
df_pivot_distributed = df_distributed.pivot_table(values='density', index='flux')
df_pivot_fixed=df_fixed.pivot_table(values='density', index='flux')
ax=df_distributed.plot.scatter(x='density',y='flux',s=5,color='#ff450099',label='distributed(4~6)')
df_fixed.plot.scatter(x='density',y='flux',s=5,color='#4169e199',label='fixed(5)',ax=ax)
plt.title('fundamentaldaigram,compare,idletime = 1800ts')
plt.legend(bbox_to_anchor=(1,1),loc='upper right',borderaxespad=0,fontsize=15)
plt.savefig('fundamentaldaigram_both_Vmax_1800ts.png',dpi=300)
plt.show()

