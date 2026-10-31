int cut_triangle_plus_y(double y0, double y1, double z1, double y2, double z2, double y3, double z3, double *y4 ,double *z4, double *y5 ,double *z5, double *y6 ,double *z6, double *y7 ,double *z7, double *y8 ,double *z8, double *y9 ,double *z9)
	{
	/*calculation of triangles cut. y0 is the position of the cut. y1 z1 y2 z2 y3 z3 is the coordinates of the triangle.
	the cut of the triangle above y value y0 gives nb_triangle (0, 1 or 2) with coordinates
	x4 z4 x5 z5 x6 z6 for the first triangle if any and x7 z7 x8 z8 x9 z9 for the second triangle if any*/
  	
  	double ymin,zmin,ymean,zmean,ymax,zmax;
  	double ymin_max,zmin_max,ymin_mean,zmin_mean,ymean_max,zmean_max;
	int nb_triangle,zimin,zimean,zimax;
	
	nb_triangle = 0;
	
	//printf("y0 %lf y1 %lf z1 %lf y2 %lf z2 %lf y3 %lf z3 %lf \n",y0,y1,z1,y2,z2,y3,z3);
	
	ymin = y1; zmin = z1; zimin = 1; zimean = 2; zimax = 3;		//default values
	if (ymin > y2)
		{
		ymin = y2;
		zmin = z2;
		zimin = 2;
		}
	if (ymin > y3)
		{
		ymin = y3;
		zmin = z3;
		zimin = 3;
		}
	ymax = y1; zmax = z1; zimax = 1; zimean = 2; zimax = 1;		//default values
	if (ymax < y2)
		{
		ymax = y2;
		zmax = z2;
		zimax = 2;
		}
	if (ymax < y3)
		{
		ymax = y3;
		zmax = z3;
		zimax = 3;
		}

	if ((zimin == 1) && (zimax == 2))
		{
		ymean = y3;
		zmean = z3;
		zimean = 3;
		}	
	if ((zimin == 1) && (zimax == 3))
		{
		ymean = y2;
		zmean = z2;
		zimean = 2;
		}	
	if ((zimin == 2) && (zimax == 3))
		{
		ymean = y1;
		zmean = z1;
		zimean = 1;
		}	
	if ((zimin == 2) && (zimax == 1))
		{
		ymean = y3;
		zmean = z3;
		zimean = 3;
		}	
	if ((zimin == 3) && (zimax == 1))
		{
		ymean = y2;
		zmean = z2;
		zimean = 2;
		}	
	if ((zimin == 3) && (zimax == 2))
		{
		ymean = y1;
		zmean = z1;
		zimean = 1;
		}	
	//printf("min %d %lf %lf mean %d %lf %lf max %d %lf %lf \n",zimin,ymin,zmin,zimean,ymean,zmean,zimax,ymax,zmax);
	
	if (y0 <= ymin)
		{
		nb_triangle = 1;
		*y4 = y1;		*z4 = z1;
		*y5 = y2;		*z5 = z2;
		*y6 = y3;		*z6 = z3;
		}
	if ((y0 > ymin) && (y0 < ymean))
		{
		nb_triangle = 2;
		ymin_max  = y0;		zmin_max  = zmin + (zmax -zmin)*(ymin_max -ymin)/(ymax -ymin);
		ymin_mean = y0;		zmin_mean = zmin + (zmean-zmin)*(ymin_mean-ymin)/(ymean-ymin);
		*y4 = ymin_max;		*z4 = zmin_max;
		*y5 = ymax;		*z5 = zmax;
		*y6 = ymin_mean;	*z6 = zmin_mean;
		*y7 = ymin_mean;	*z7 = zmin_mean;
		*y8 = ymax;		*z8 = zmax;
		*y9 = ymean;		*z9 = zmean;
		}
	if ((y0 >= ymean) && (y0 < ymax))
		{
		nb_triangle = 1;
		ymin_max  = y0;		zmin_max  = zmin + (zmax -zmin)*(ymin_max -ymin)/(ymax -ymin);
		ymean_max = y0;		zmean_max = zmean + (zmax-zmean)*(ymean_max-ymean)/(ymax-ymean);
		*y4 = ymin_max;		*z4 = zmin_max;
		*y5 = ymax;		*z5 = zmax;
		*y6 = ymean_max;	*z6 = zmean_max;
		}
	if (y0 >= ymax)
		{
		nb_triangle = 0;
		}

  	return nb_triangle;
	}
	
	
int cut_triangle_moin_y(double y0, double y1, double z1, double y2, double z2, double y3, double z3, double *y4 ,double *z4, double *y5 ,double *z5, double *y6 ,double *z6, double *y7 ,double *z7, double *y8 ,double *z8, double *y9 ,double *z9)
	{
	/*calculation of triangles cut. y0 is the position of the cut. y1 z1 y2 z2 y3 z3 is the coordinates of the triangle.
	the cut of the triangle below y value y0 gives nb_triangle (0, 1 or 2) with coordinates
	x4 z4 x5 z5 x6 z6 for the first triangle if any and x7 z7 x8 z8 x9 z9 for the second triangle if any*/
	double y10,z10,y11,z11,y12,z12,y13,z13,y14,z14,y15,z15;
	int nb_triangle;
	
	nb_triangle = 0;
  	
	nb_triangle =  cut_triangle_plus_y(-y0, -y1, z1, -y2, z2, -y3, z3, &y10 ,&z10, &y11 ,&z11, &y12 ,&z12, &y13 ,&z13, &y14 ,&z14, &y15 ,&z15);
	*y4 = - y10;	*z4 = + z10;
	*y5 = - y11;	*z5 = + z11;
	*y6 = - y12;	*z6 = + z12;
	*y7 = - y13;	*z7 = + z13;
	*y8 = - y14;	*z8 = + z14;
	*y9 = - y15;	*z9 = + z15;
	
  	return nb_triangle;
	}
	
int cut_triangle_plus_z(double z0, double y1, double z1, double y2, double z2, double y3, double z3, double *y4 ,double *z4, double *y5 ,double *z5, double *y6 ,double *z6, double *y7 ,double *z7, double *y8 ,double *z8, double *y9 ,double *z9)
	{
	/*calculation of triangles cut. y0 is the position of the cut. y1 z1 y2 z2 y3 z3 is the coordinates of the triangle.
	the cut of the triangle below y value y0 gives nb_triangle (0, 1 or 2) with coordinates
	x4 z4 x5 z5 x6 z6 for the first triangle if any and x7 z7 x8 z8 x9 z9 for the second triangle if any*/
	double y10,z10,y11,z11,y12,z12,y13,z13,y14,z14,y15,z15;
	int nb_triangle;
	
	nb_triangle = 0;
  	
	nb_triangle =  cut_triangle_plus_y(z0, z1, y1, z2, y2, z3, y3, &y10 ,&z10, &y11 ,&z11, &y12 ,&z12, &y13 ,&z13, &y14 ,&z14, &y15 ,&z15);
	*y4 = z10;	*z4 = y10;
	*y5 = z11;	*z5 = y11;
	*y6 = z12;	*z6 = y12;
	*y7 = z13;	*z7 = y13;
	*y8 = z14;	*z8 = y14;
	*y9 = z15;	*z9 = y15;
	
  	return nb_triangle;
	}
	
int cut_triangle_moin_z(double z0, double y1, double z1, double y2, double z2, double y3, double z3, double *y4 ,double *z4, double *y5 ,double *z5, double *y6 ,double *z6, double *y7 ,double *z7, double *y8 ,double *z8, double *y9 ,double *z9)
	{
	/*calculation of triangles cut. y0 is the position of the cut. y1 z1 y2 z2 y3 z3 is the coordinates of the triangle.
	the cut of the triangle below y value y0 gives nb_triangle (0, 1 or 2) with coordinates
	x4 z4 x5 z5 x6 z6 for the first triangle if any and x7 z7 x8 z8 x9 z9 for the second triangle if any*/
	double y10,z10,y11,z11,y12,z12,y13,z13,y14,z14,y15,z15;
	int nb_triangle;
	
	nb_triangle = 0;
  	
	nb_triangle =  cut_triangle_plus_y(-z0, -z1, y1, -z2, y2, -z3, y3, &y10 ,&z10, &y11 ,&z11, &y12 ,&z12, &y13 ,&z13, &y14 ,&z14, &y15 ,&z15);
	*y4 = z10;	*z4 = - y10;
	*y5 = z11;	*z5 = - y11;
	*y6 = z12;	*z6 = - y12;
	*y7 = z13;	*z7 = - y13;
	*y8 = z14;	*z8 = - y14;
	*y9 = z15;	*z9 = - y15;
	
  	return nb_triangle;
	}
	
int cut_segment_plus_y(double y0, double y1, double z1, double y2, double z2, double *y4 ,double *z4, double *y5 ,double *z5)
	{
	/*calculation of segment cut. y0 is the position of the cut. y1 z1 y2 z2 is the coordinates of the segment.
	the cut of the triangle above y value y0 gives nb_segment (0 or 1) with coordinates
	x4 z4 x5 z5 for the segment if any*/
  	
  	double ymin,zmin,ymean,zmean,ymax,zmax;
  	double ymin_max,zmin_max,ymin_mean,zmin_mean,ymean_max,zmean_max;
	int nb_segment,zimin,zimean,zimax;
	
	nb_segment = 0;
	
	//printf("y0 %lf y1 %lf z1 %lf y2 %lf z2 %lf y3 %lf z3 %lf \n",y0,y1,z1,y2,z2,y3,z3);
	

	if (y1 <= y2)
		{
		ymin = y1; zmin = z1; zimin = 1; 	
		ymax = y2; zmax = z2; zimax = 2;
		}
	else
		{
		ymin = y2; zmin = z2; zimin = 2; 	
		ymax = y1; zmax = z1; zimax = 1;
		}
	//printf("min %d %lf %lf mean %d %lf %lf max %d %lf %lf \n",zimin,ymin,zmin,zimean,ymean,zmean,zimax,ymax,zmax);
	
	if (y0 <= ymin)
		{
		nb_segment = 1;
		*y4 = y1;		*z4 = z1;
		*y5 = y2;		*z5 = z2;
		}
	if ((y0 >= ymin) && (y0 < ymax))
		{
		nb_segment = 1;
		ymin_max  = y0;		zmin_max  = zmin + (zmax -zmin)*(ymin_max -ymin)/(ymax -ymin);
		*y4 = ymin_max;		*z4 = zmin_max;
		*y5 = ymax;		*z5 = zmax;
		}
	if (y0 >= ymax)
		{
		nb_segment = 0;
		}

  	return nb_segment;
	}
	
int cut_segment_moin_y(double y0, double y1, double z1, double y2, double z2, double *y4 ,double *z4, double *y5 ,double *z5)
	{
	/*calculation of segments cut. y0 is the position of the cut. y1 z1 y2 z2 y3 z3 is the coordinates of the segment.
	the cut of the segment below y value y0 gives nb_segment (0, 1 or 2) with coordinates
	x4 z4 x5 z5 x6 z6 for the first segment if any and x7 z7 x8 z8 x9 z9 for the second segment if any*/
	double y10,z10,y11,z11,y12,z12,y13,z13,y14,z14,y15,z15;
	int nb_segment;
	
	nb_segment = 0;
  	
	nb_segment =  cut_segment_plus_y(-y0, -y1, z1, -y2, z2, &y10 ,&z10, &y11 ,&z11);
	*y4 = - y10;	*z4 = + z10;
	*y5 = - y11;	*z5 = + z11;
	
  	return nb_segment;
	}
	
int cut_segment_plus_z(double z0, double y1, double z1, double y2, double z2, double *y4 ,double *z4, double *y5 ,double *z5)
	{
	/*calculation of segments cut. y0 is the position of the cut. y1 z1 y2 z2 y3 z3 is the coordinates of the segment.
	the cut of the segment below y value y0 gives nb_segment (0, 1 or 2) with coordinates
	x4 z4 x5 z5 x6 z6 for the first segment if any and x7 z7 x8 z8 x9 z9 for the second segment if any*/
	double y10,z10,y11,z11,y12,z12,y13,z13,y14,z14,y15,z15;
	int nb_segment;
	
	nb_segment = 0;
  	
	nb_segment =  cut_segment_plus_y(z0, z1, y1, z2, y2, &y10 ,&z10, &y11 ,&z11);
	*y4 = z10;	*z4 = y10;
	*y5 = z11;	*z5 = y11;
	
  	return nb_segment;
	}
	
int cut_segment_moin_z(double z0, double y1, double z1, double y2, double z2, double *y4 ,double *z4, double *y5 ,double *z5)
	{
	/*calculation of segments cut. y0 is the position of the cut. y1 z1 y2 z2 y3 z3 is the coordinates of the segment.
	the cut of the segment below y value y0 gives nb_segment (0, 1 or 2) with coordinates
	x4 z4 x5 z5 x6 z6 for the first segment if any and x7 z7 x8 z8 x9 z9 for the second segment if any*/
	double y10,z10,y11,z11,y12,z12,y13,z13,y14,z14,y15,z15;
	int nb_segment;
	
	nb_segment = 0;
  	
	nb_segment =  cut_segment_plus_y(-z0, -z1, y1, -z2, y2, &y10 ,&z10, &y11 ,&z11);
	*y4 = z10;	*z4 = - y10;
	*y5 = z11;	*z5 = - y11;
	
  	return nb_segment;
	}
	
	
int cut_segment_plus_x(double x0, double x1, double y1, double x2, double y2, double *x4 ,double *y4, double *x5 ,double *y5)
	{
	/*calculation of segments cut. x0 is the position of the cut. x1 y1 x2 y2 x3 y3 is the coordinates of the segment.
	the cut of the segment below x value x0 gives nb_segment (0, 1 or 2) with coordinates
	x4 y4 x5 y5 x6 y6 for the first segment if any and x7 y7 x8 y8 x9 y9 for the second segment if any*/
	double x10,y10,x11,y11,x12,y12,x13,y13,x14,y14,x15,y15;
	int nb_segment;
	
	nb_segment = 0;
  	
	nb_segment =  cut_segment_plus_y(x0, x1, y1, x2, y2, &x10 ,&y10, &x11 ,&y11);
	*x4 = x10;	*y4 = y10;
	*x5 = x11;	*y5 = y11;
	
	//printf("x0 %lf x1 %lf y1 %lf x2 %lf y2 %lf x4 %lf y4 %lf x5 %lf y5 %lf \n",x0,x1,y1,x2,y2,*x4,*y4,*x5,*y5);
	
  	return nb_segment;
	}
	
int cut_segment_moin_x(double x0, double x1, double y1, double x2, double y2, double *x4 ,double *y4, double *x5 ,double *y5)
	{
	/*calculation of segments cut. x0 is the position of the cut. x1 y1 x2 y2 x3 y3 is the coordinates of the segment.
	the cut of the segment below x value x0 gives nb_segment (0, 1 or 2) with coordinates
	x4 y4 x5 y5 x6 y6 for the first segment if anx and x7 y7 x8 y8 x9 y9 for the second segment if anx*/
	double x10,y10,x11,y11,x12,y12,x13,y13,x14,y14,x15,y15;
	int nb_segment;
	
	nb_segment = 0;
  	
	nb_segment =  cut_segment_plus_y(-x0, -x1, y1, -x2, y2, &x10 ,&y10, &x11 ,&y11);
	*x4 = -x10;	*y4 = y10;
	*x5 = -x11;	*y5 = y11;
	
  	return nb_segment;
	}
	
	

