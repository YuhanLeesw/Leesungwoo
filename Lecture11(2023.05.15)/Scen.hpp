//#include<vector>
//
//
//class Object; // Object Ŭ������ ����. ���� ���Ǵ� Object.hpp���� �̷���� ��
//namespace MuSoenu 
//{
//    class Scene
//    {
//    private:
//        int width; //ȭ�� ����
//        int height;//ȭ�� ����
//        //screenBuf[width + (width * height)];
//        char* screenBuf;//ȭ�� ����
//        std::vector<Object*> objList; //Scene�� ���Ե� Object���� ������ ����
//    
//    public:
//        Scene();//������
//        ~Scene();//�Ҹ���
//        
//        void add_object(Object* object); // Scene�� Object�� �߰��ϴ� �޼���.
//        void remove_object(Object* object); // Scene���� Object�� �����ϴ� �޼���.
//
//        void draw(); // Scene�� �ִ� ��� Object���� �׸��� �޼���.
//
//        void InitScreenBuf() // ȭ�� ���� �ʱ�ȭ
//        {
//            screenBuf = new char[(width + 1) * height + 5];
//
//            for (int i; i < height; i++)
//            {
//                screenBuf[(width + 1) + (width + 1) * i - 1] = '\n';
//            }
//            screenBuf[(width + 1) + (width + 1) * (height - 1) - 1] = '\0';
//        }
//
//        void ReleaseScreenBuf()// ȭ�� ���� �޸� ����
//        {
//            if (screenBuf != nullptr)
//            {
//                delete(screenBuf);
//            }
//        }
//
//        void DrawScreenBuf() // ȭ�� ���� �׸���
//        {
//            std::cout << screenBuf;
//        }
//    };
//}
