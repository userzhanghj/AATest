#ifndef _AI_SFR_H_
#define _AI_SFR_H_

#ifndef AI_EXPORT_SFR
#define AI_EXPORT_SFR extern "C" __declspec(dllimport) 
#endif

#define ALPHA 4.0

#define HIGH_CLIP(x,limit)		( ((x)>(limit)) ? (limit):(x) )
#define LOW_CLIP(x,limit)		( ((x)<(limit)) ? (limit):(x) )
#define CLIP(x,l,h)				HIGH_CLIP(LOW_CLIP(x,l),h)


AI_EXPORT_SFR int sfr_proc(BYTE *roi, int roi_w, int roi_h, int t_cnt, double *t_freq, 
	double *t_sfr, double &slope, double &offset, double *esf, double *lsf, double *freq, double *amp);
AI_EXPORT_SFR int mtf(const double *freq, const double *amp, double mtfx, double &mtfx_freq, int x_cnt);
AI_EXPORT_SFR int mtfp(const double *freq, const double *amp, int mtfxp, double &mtf_val, double &mtf50p_freq, int x_cnt);

namespace ns_sfr
{
	AI_EXPORT_SFR int	 search_edge(BYTE *roi, double *shift, int roi_w, int roi_h);
	AI_EXPORT_SFR int	 shift_centroids(double *shift,  double *temp, int roi_h, double &offset);
	AI_EXPORT_SFR int	 fit(int roi_h, double *x, double *y, double &slope, double &offset);
	AI_EXPORT_SFR int	 check_slope(double slope, int &size_y, int *numcycles, double mincyc);
	AI_EXPORT_SFR int	 bin_to_regular_xgrid(int alpha, double *edgex, double *signal, double *ave_edge, int *counts, int size_x, int size_y);

	AI_EXPORT_SFR void   apply_hamming_window(int alpha, int oldlen, int newxwidth, double *ave_edge, int *pcnt2);
	AI_EXPORT_SFR int    ftwos(int number, double dx, double *lsf, int ns, double ds, double *sfr);
	AI_EXPORT_SFR void   locate_max_psf(int len, double *AveEdge, int *pcnt2);
	AI_EXPORT_SFR int    get_esf2(BYTE *roi, int roi_w, int roi_h, double *shift, double *esf, double &slope, double &offset);
	AI_EXPORT_SFR int    get_lsf2(double *esf, double *lsf, int bin_len, double &centroid);

	AI_EXPORT_SFR int	 get_dft2(double *lsf, double *sfr, double *freq, int bin_len);
	AI_EXPORT_SFR double get_continue_mtf2(const double *amplitude, const double *frequency, double x, int x_cnt);
}


#endif