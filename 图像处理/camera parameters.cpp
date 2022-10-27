//camera parameter.cpp----select industrial camera
# include <iostream>
# include <string>
# include <cmath>

//the parameters of camera
//CCD or CMOS �������ߴ�
//1/2.5"===4.3*5.8
const double CCD_LENTH = 4.3;//����������mm
const double CCD_HIGHT = 5.8;//���������mm
const double F_DISTANCE = 2500;//���mm
//֡��
const double FRAME = 24.0;//fps---frame per second
//�ӿ�����
enum interface { C, CS };
//�ֱ���
int DPI_LEN_NUM = 2592;//�ֱ��ʺ�
int DPI_HIG_NUM = 1944;//�ֱ�����
//���سߴ�
double SIZE_LEN = 2.2;//���سߴ�um
double SIZE_HIG = 2.2;//���سߴ�um
//�����ӿ�

class camera
{
private:
	double ccd_length;
	double ccd_hight;
	enum interface { C, CS };
	//	std::string inter_elec[2] = { "USB3.0", "GIGE����" };
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
	std::cout << "��������������Ѿ�����......" << std::endl;
}
//camera::camera(double len , double hig, double frame , double size_l , double size_h ,double dpi_l,double dpi_h) :
//ccd_length(len), ccd_hight(hig), frame(frame), size_len(size_l), size_hig(size_h)
//{
//	dpi_len =dpi_l ;
//	dpi_hig = dpi_h;
//	std::cout << "��������������Ѿ�����......" << std::endl;
//
//}
camera::camera(const camera& ca, double dpi_l, double dpi_h) :
	camera(ca)
{
	dpi_len = dpi_l;
	dpi_hig = dpi_h;
	std::cout << "��������������Ѿ��ı�......" << std::endl;
}


//��ͷ����
class lens
{
private:
	//�ӿ�
	enum interface { C, CS };
	//����ߴ�  :mm
	double size_target_len;//��ͷ����ߴ��
	double size_target_hig;//��ͷ����ߴ���
	//����  :mm
	double f;//����
	//��Ȧ��Χ ����ȦֵԽ�󣬹���ԽС
	double F;//��Ȧ
	//�ӳ���  ˮƽ����ֱ���Խ���,   ����
	double angle_h;//ˮƽ�ӳ���
	double angle_v;//��ֱ�ӳ���
	double angle_diag;
	//�۽���Χ,���಻�ɱ䣬����ͨ���ı�CCD���ı�Խ�����
	double focus_range;//�۽���Χ
	//��ɢԲֱ�� :mm
	double delta;//��ɢԲֱ��
	//����  :mm
	double depth_of_filed_former;//ǰ����
	double depth_of_filed_laster;//����
	double depth_of_filed;//����
public:
	//�������ʼ����ͷ����
	lens(double size_target1 = 29.0, double size_target2 = 29.0, double f = 4
		, double F = 16);
	double deltafun(double size_cam_len, double size_cam_high, const int p = 1730);
	double depth_of_filedfun(double f_distance);
	int piexl(double target_length, double target_hight, double precision);//ȷ������
	void angle_filed(double cam_length, double cam_hight);//�ӳ���
	bool surpass_focus(double f_distance = F_DISTANCE); //������
	bool adapter_lens(double size_cam_len, double size_cam_high);//��ͷ�ߴ��Ƿ���ڴ������ߴ�
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
		std::cout << "��ѡ��ͷ��ǰ����Ϊ��" << depth_of_filed_former << std::endl;
		std::cout << "��ѡ��ͷ�ĺ���Ϊ��" << depth_of_filed_laster << std::endl;
		double depth = depth_of_filed_former + depth_of_filed_laster;
		std::cout << "��ѡ��ͷ����Ϊ��" << depth << std::endl;

		return depth;
	}
	else
	{
		std::cout << "��ѡ��ͷ����Ϊ�����" << std::endl;

		return 0;
	}

}
int lens::piexl(double target_length, double target_hight, double precision)//ȷ������
{
	double piexl_length = target_length / precision;
	double piexl_hight = target_hight / precision;
	std::cout << "�������õķֱ���Ϊ��" << piexl_length << "*" << piexl_hight << std::endl;
	return (int)(piexl_length * piexl_hight);
}
void lens::angle_filed(double cam_length, double cam_hight)//�ӳ���
{
	angle_h = 2 * atan(cam_length / 2 / f);
	angle_v = 2 * atan(cam_hight / 2 / f);
	double d = sqrt((cam_length * cam_length) + (cam_hight * cam_hight));
	angle_diag = 2 * atan(d / 2 / f);
	std::cout << "��ͷ��ˮƽ�ӳ���Ϊ��" << angle_h * 180 / 3.14 << std::endl;
	std::cout << "��ͷ�Ĵ�ֱ�ӳ���Ϊ��" << angle_v * 180 / 3.14 << std::endl;
	std::cout << "��ͷ��ˮƽ�ӳ���Ϊ��" << angle_diag * 180 / 3.14 << std::endl;
}
bool lens::surpass_focus(double f_distance) //������
{

	if ((f * f - F * delta * f_distance) <= 0)
	{
		std::cout << "���ֳ�����������۽���Χ�����\n";
		return true;
	}

	else
		return false;
}
bool lens::adapter_lens(double size_cam_len, double size_cam_high)//��ͷ�ߴ��Ƿ���ڴ������ߴ�
{
	if (size_cam_high < size_target_hig && size_cam_len < size_target_len)
	{
		std::cout << "��ͷ�ߴ���ڴ������ߴ磬���Խ��ܣ�\n";
		return true;
	}
	else
	{
		std::cout << "��ͷ�ߴ�С�ڴ������ߴ磬�����ܣ�\n";
		return false;
	}

}
double lens::focus_select(double size_target_max, double size_cam_min, double distance_target)
{
	double select_f = size_cam_min * distance_target / size_target_max;
	std::cout << "�������ý���Ϊ��" << select_f << std::endl;
	return select_f;
}
double size_target_max1(double& a, double& b) { return (a > b) ? a : b; };
int main0()
{
	//����ȷ����Ұ��Χ�;�ͷ��Ŀ��ľ���
	double filed_len = 1500;
	double filed_hig = 1500;
	double f_distance = F_DISTANCE;

	//�����������������
	camera c1;
	camera c2(c1, 1920, 1200);

	//��ȡ�������ߴ�
	double cam_len = c1.cam_len();
	double cam_hig = c1.cam_hig();

	//������ͷ����
	lens lens1;
	if (lens1.adapter_lens(cam_len, cam_hig))
	{
		double delta = lens1.deltafun(c2.cam_len(), c2.cam_hig());
		//�����ʽ����
		//set format to ##.##
		std::ios_base::fmtflags orig =
			std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
		std::streamsize prec = std::cout.precision(2);
		int piex = lens1.piexl(filed_len, filed_hig, 1);
		lens1.angle_filed(c2.cam_len(), c2.cam_hig());
		std::cout << "��������Ҫ�������Χ��������÷ֱ���Ϊ��" << piex << std::endl;
		/*std::cout << "���ݴ�����������õľ�ͷ���ӳ���Ϊ��\n " <<
			"ˮƽ�ӳ���Ϊ��" << lens1.rangle_h() << "\n"
			<< "��ֱ�ӳ���Ϊ��" << lens1.rangle_v() << std::endl;*/
		std::cout.setf(orig, std::ios_base::floatfield);
		std::cout.precision(prec);
		double distance = 1510;//�Խ�����:��ͷ����������뾵ͷ�������֮��
		double depth = lens1.depth_of_filedfun(f_distance);
		double size_target_max = size_target_max1(filed_len, filed_hig);
		double size_cam_min = c2.size_cam_min();
		double f_select = lens1.focus_select(size_target_max, size_cam_min, f_distance);
	}
	else
		std::cout << "ѡ�õľ�ͷ�����ʣ�\n";
	//system("pause");
	return 0;
}