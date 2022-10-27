//camera parameter.cpp----select industrial camera
# include <iostream>
# include <string>
# include <cmath>

//the parameters of camera
//CCD or CMOS 传感器尺寸
//1/2.5"===4.3*5.8
const double CCD_LENTH = 4.3;//传感器长度mm
const double CCD_HIGHT = 5.8;//传感器宽度mm
const double F_DISTANCE = 2500;//物距mm
//帧率
const double FRAME = 24.0;//fps---frame per second
//接口类型
enum interface { C, CS };
//分辨率
int DPI_LEN_NUM = 2592;//分辨率横
int DPI_HIG_NUM = 1944;//分辨率纵
//像素尺寸
double SIZE_LEN = 2.2;//像素尺寸um
double SIZE_HIG = 2.2;//像素尺寸um
//电气接口

class camera
{
private:
	double ccd_length;
	double ccd_hight;
	enum interface { C, CS };
	//	std::string inter_elec[2] = { "USB3.0", "GIGE网口" };
	double frame;
	int dpi_len;
	int dpi_hig;
	double size_len;
	double size_hig;
public:
	camera(double len = CCD_LENTH, double hig = CCD_HIGHT, double frame = FRAME, double size_l = SIZE_LEN, double size_h = SIZE_HIG, double dpi_len = DPI_LEN_NUM,
		double dpi_hig = DPI_HIG_NUM);
	//camera(double len, double hig, double frame, double size_l, double size_h, double dpi_l, double dpi_h);
	camera(const camera& ca, double dpi_l, double dpi_h);
	double cam_len()const { return ccd_length; }
	double cam_hig()const { return ccd_hight; }
	double size_cam_min()const { return (ccd_length > ccd_hight) ? ccd_length : ccd_hight; };
};

camera::camera(double len, double hig, double frame, double size_l, double size_h, double dpi_len,
	double dpi_hig) :
	ccd_length(len), ccd_hight(hig), frame(frame), size_len(size_l), size_hig(size_h), dpi_len(dpi_len), dpi_hig(dpi_hig)
{
	std::cout << "相机传感器参数已经生成......" << std::endl;
}
//camera::camera(double len , double hig, double frame , double size_l , double size_h ,double dpi_l,double dpi_h) :
//ccd_length(len), ccd_hight(hig), frame(frame), size_len(size_l), size_hig(size_h)
//{
//	dpi_len =dpi_l ;
//	dpi_hig = dpi_h;
//	std::cout << "相机传感器参数已经生成......" << std::endl;
//
//}
camera::camera(const camera& ca, double dpi_l, double dpi_h) :
	camera(ca)
{
	dpi_len = dpi_l;
	dpi_hig = dpi_h;
	std::cout << "相机传感器参数已经改变......" << std::endl;
}


//镜头参数
class lens
{
private:
	//接口
	enum interface { C, CS };
	//靶面尺寸  :mm
	double size_target_len;//镜头靶面尺寸横
	double size_target_hig;//镜头靶面尺寸纵
	//焦距  :mm
	double f;//焦距
	//光圈范围 ，光圈值越大，光流越小
	double F;//光圈
	//视场角  水平，垂直，对角线,   ：°
	double angle_h;//水平视场角
	double angle_v;//垂直视场角
	double angle_diag;
	//聚焦范围,焦距不可变，可以通过改变CCD来改变对焦距离
	double focus_range;//聚焦范围
	//弥散圆直径 :mm
	double delta;//弥散圆直径
	//景深  :mm
	double depth_of_filed_former;//前景深
	double depth_of_filed_laster;//后景深
	double depth_of_filed;//景深
public:
	//在这里初始化镜头参数
	lens(double size_target1 = 29.0, double size_target2 = 29.0, double f = 4
		, double F = 16);
	double deltafun(double size_cam_len, double size_cam_high, const int p = 1730);
	double depth_of_filedfun(double f_distance);
	int piexl(double target_length, double target_hight, double precision);//确定像素
	void angle_filed(double cam_length, double cam_hight);//视场角
	bool surpass_focus(double f_distance = F_DISTANCE); //超焦距
	bool adapter_lens(double size_cam_len, double size_cam_high);//镜头尺寸是否大于传感器尺寸
	double focus_select(double size_target_max, double size_cam_min, double distance_target);
	double rangle_h()const { return angle_h; }
	double rangle_v()const { return angle_v; }
	double rangle_diag()const { return angle_diag; }


};
lens::lens(double size_target1, double size_target2, double f, double F) :
	size_target_len(size_target1), size_target_hig(size_target2), f(f), F(F)
{
}
double lens::deltafun(double size_cam_len, double size_cam_high, const int p)
{
	delta = sqrt((size_cam_len * size_cam_len) + (size_cam_high * size_cam_high)) / p;
	std::cout << "delta: " << delta << std::endl;
	return delta;
}
double lens::depth_of_filedfun(double f_distance)
{
	depth_of_filed_former = F * delta * f_distance * f_distance / (f * f + F * delta * f_distance);
	if (!surpass_focus())
	{

		depth_of_filed_laster = F * delta * f_distance * f_distance / (f * f - F * delta * f_distance);
		std::cout << "所选镜头的前景深为：" << depth_of_filed_former << std::endl;
		std::cout << "所选镜头的后景深为：" << depth_of_filed_laster << std::endl;
		double depth = depth_of_filed_former + depth_of_filed_laster;
		std::cout << "所选镜头景深为：" << depth << std::endl;

		return depth;
	}
	else
	{
		std::cout << "所选镜头景深为无穷大！" << std::endl;

		return 0;
	}

}
int lens::piexl(double target_length, double target_hight, double precision)//确定像素
{
	double piexl_length = target_length / precision;
	double piexl_hight = target_hight / precision;
	std::cout << "计算所得的分辨率为：" << piexl_length << "*" << piexl_hight << std::endl;
	return (int)(piexl_length * piexl_hight);
}
void lens::angle_filed(double cam_length, double cam_hight)//视场角
{
	angle_h = 2 * atan(cam_length / 2 / f);
	angle_v = 2 * atan(cam_hight / 2 / f);
	double d = sqrt((cam_length * cam_length) + (cam_hight * cam_hight));
	angle_diag = 2 * atan(d / 2 / f);
	std::cout << "镜头的水平视场角为：" << angle_h * 180 / 3.14 << std::endl;
	std::cout << "镜头的垂直视场角为：" << angle_v * 180 / 3.14 << std::endl;
	std::cout << "镜头的水平视场角为：" << angle_diag * 180 / 3.14 << std::endl;
}
bool lens::surpass_focus(double f_distance) //超焦距
{

	if ((f * f - F * delta * f_distance) <= 0)
	{
		std::cout << "出现超焦距情况，聚焦范围无穷大！\n";
		return true;
	}

	else
		return false;
}
bool lens::adapter_lens(double size_cam_len, double size_cam_high)//镜头尺寸是否大于传感器尺寸
{
	if (size_cam_high < size_target_hig && size_cam_len < size_target_len)
	{
		std::cout << "镜头尺寸大于传感器尺寸，可以接受！\n";
		return true;
	}
	else
	{
		std::cout << "镜头尺寸小于传感器尺寸，不接受！\n";
		return false;
	}

}
double lens::focus_select(double size_target_max, double size_cam_min, double distance_target)
{
	double select_f = size_cam_min * distance_target / size_target_max;
	std::cout << "计算所得焦距为：" << select_f << std::endl;
	return select_f;
}
double size_target_max1(double& a, double& b) { return (a > b) ? a : b; };
int main0()
{
	//首先确定视野范围和镜头到目标的距离
	double filed_len = 1500;
	double filed_hig = 1500;
	double f_distance = F_DISTANCE;

	//创建相机传感器对象
	camera c1;
	camera c2(c1, 1920, 1200);

	//读取传感器尺寸
	double cam_len = c1.cam_len();
	double cam_hig = c1.cam_hig();

	//创建镜头对象
	lens lens1;
	if (lens1.adapter_lens(cam_len, cam_hig))
	{
		double delta = lens1.deltafun(c2.cam_len(), c2.cam_hig());
		//输出格式设置
		//set format to ##.##
		std::ios_base::fmtflags orig =
			std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
		std::streamsize prec = std::cout.precision(2);
		int piex = lens1.piexl(filed_len, filed_hig, 1);
		lens1.angle_filed(c2.cam_len(), c2.cam_hig());
		std::cout << "根据物体要求测量范围及精度求得分辨率为：" << piex << std::endl;
		/*std::cout << "根据传感器参数求得的镜头的视场角为：\n " <<
			"水平视场角为：" << lens1.rangle_h() << "\n"
			<< "垂直视场角为：" << lens1.rangle_v() << std::endl;*/
		std::cout.setf(orig, std::ios_base::floatfield);
		std::cout.precision(prec);
		double distance = 1510;//对焦距离:镜头到物体距离与镜头到像距离之和
		double depth = lens1.depth_of_filedfun(f_distance);
		double size_target_max = size_target_max1(filed_len, filed_hig);
		double size_cam_min = c2.size_cam_min();
		double f_select = lens1.focus_select(size_target_max, size_cam_min, f_distance);
	}
	else
		std::cout << "选用的镜头不合适！\n";
	//system("pause");
	return 0;
}