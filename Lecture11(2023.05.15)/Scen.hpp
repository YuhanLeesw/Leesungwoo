//#include<vector>
//
//
//class Object; // Object 클래스의 선언. 실제 정의는 Object.hpp에서 이루어질 것
//namespace MuSoenu 
//{
//    class Scene
//    {
//    private:
//        int width; //화면 넓이
//        int height;//화면 높이
//        //screenBuf[width + (width * height)];
//        char* screenBuf;//화면 버퍼
//        std::vector<Object*> objList; //Scene에 포함된 Object들을 저장할 백터
//    
//    public:
//        Scene();//생성자
//        ~Scene();//소멸자
//        
//        void add_object(Object* object); // Scene에 Object를 추가하는 메서드.
//        void remove_object(Object* object); // Scene에서 Object를 제거하는 메서드.
//
//        void draw(); // Scene에 있는 모든 Object들을 그리는 메서드.
//
//        void InitScreenBuf() // 화면 버퍼 초기화
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
//        void ReleaseScreenBuf()// 화면 버퍼 메모리 해제
//        {
//            if (screenBuf != nullptr)
//            {
//                delete(screenBuf);
//            }
//        }
//
//        void DrawScreenBuf() // 화면 버퍼 그리기
//        {
//            std::cout << screenBuf;
//        }
//    };
//}
