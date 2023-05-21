//#include "Component.hpp"
//#include<vector>
//#include <algorithm>
//#pragma once
//
//class Component; // Component 클래스의 선언. 실제 정의는 Component.hpp에서 이루어질 것
//
//class Object
//{
//private:
//    std::vector<Component*> components; // Object가 가지고 있는 Component들을 저장할 벡터.
//    float x, y; // Object의 위치
//    float scale; // Object의 크기
//    float rotation; // Object의 회전 각도
//
//public:
//    Object() {}; // 생성자
//    ~Object() { // 소멸자
//        for (Component* component : components) {
//            delete component; // 각 Component 메모리 해제
//        }
//    }
//    void AddComponent(Component* component) {// Object에 Component를 추가하는 메서드.
//        components.push_back(component);
//    } 
//    void RemoveComponent(Component* component) { // Object에서 Component를 제거하는 메서드.
//        components.erase(std::remove(components.begin(), components.end(), component), components.end());
//        delete component; // Component 메모리 해제
//    } 
//
//    void Render() {// Object를 그리는 메서드.
//        for (Component* component : components) {
//            component->Render(); // 각 Component의 Render 메서드 호출
//        }
//    } 
//    
//
//};