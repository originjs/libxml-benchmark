/* Huge speed optimization posible:
	Replace corelation matrix on square of correlation matrix, it will
	remove need of cpu-consuming sqrt function
*/
#include <math.h>

// 解析时间的统计变量
unsigned long disp_n;
unsigned long disp_s;
double disp_d;
double disp_m;

// 保存时间的统计变量
unsigned long save_disp_n;
unsigned long save_disp_s;
double save_disp_d;
double save_disp_m;

void disp_init() {
	// 初始化解析统计
	disp_n=0;
	disp_s=0;
	disp_d=0;
	
	// 初始化保存统计
	save_disp_n=0;
	save_disp_s=0;
	save_disp_d=0;
}

// 解析时间的统计函数
void disp_event(unsigned long disp_v) {
	unsigned long t;
	
	disp_n++;
	t=disp_n*(disp_n-1);
	
	disp_s+=disp_v;
	disp_v*=disp_n;

	if (t) disp_d+=(double)(((disp_s-disp_v)*(disp_s-disp_v)))/t;
}

// 保存时间的统计函数
void save_disp_event(unsigned long disp_v) {
	unsigned long t;
	
	save_disp_n++;
	t = save_disp_n*(save_disp_n-1);
	
	save_disp_s += disp_v;
	disp_v *= save_disp_n;

	if (t) save_disp_d += (double)(((save_disp_s-disp_v)*(save_disp_s-disp_v)))/t;
}

void disp_post() {
	// 计算解析统计结果
	if (disp_n>0) {
		disp_m = ((double)disp_s) / disp_n;
		if (disp_n>1) {
			disp_d /= (disp_n-1);
			disp_d = sqrt(disp_d);
		}
	}
	
	// 计算保存统计结果
	if (save_disp_n > 0) {
		save_disp_m = ((double)save_disp_s) / save_disp_n;
		if (save_disp_n > 1) {
			save_disp_d /= (save_disp_n-1);
			save_disp_d = sqrt(save_disp_d);
		}
	}
}	
