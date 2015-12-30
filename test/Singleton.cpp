#include <iostream>
using namespace std;
class Singleton
{
	public:
		static Singleton* GetInstance()
		{
			if(NULL == instance_)
			{
				instance_ = new Singleton;
			}

			return instance_;
		}
		~Singleton()
		{
			cout << "~Singleton ..." << endl;
		}
		static void Free()
		{
			if(NULL != instance_ )
			{
				delete instance_;
			}
		}
	private:
		Singleton(const Singleton&  other);
		Singleton&  operator=(const Singleton&  other);
		Singleton()
		{
			cout << "Singleton ..." << endl;
		}
		class Garbo
		{
			public:
				~Garbo()
				{
					if(Singleton::instance_ != NULL)
					{
						cout << "hhhhh" << endl;
						delete instance_; 
						cout << "kkkkk" << endl;
					}
				}
		};
		static Singleton*  instance_;  
		static Garbo garbo_;  
};

Singleton::Garbo Singleton::garbo_;  
Singleton*  Singleton::instance_;

int main(void)
{

	Singleton*  s = Singleton::GetInstance();
	Singleton*  s1 = Singleton::GetInstance();

		return 0;
}
