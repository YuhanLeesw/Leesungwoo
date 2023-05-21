//#include "Component.hpp"
//#include<vector>
//#include <algorithm>
//#pragma once
//
//class Component; // Component Ŭ������ ����. ���� ���Ǵ� Component.hpp���� �̷���� ��
//
//class Object
//{
//private:
//    std::vector<Component*> components; // Object�� ������ �ִ� Component���� ������ ����.
//    float x, y; // Object�� ��ġ
//    float scale; // Object�� ũ��
//    float rotation; // Object�� ȸ�� ����
//
//public:
//    Object() {}; // ������
//    ~Object() { // �Ҹ���
//        for (Component* component : components) {
//            delete component; // �� Component �޸� ����
//        }
//    }
//    void AddComponent(Component* component) {// Object�� Component�� �߰��ϴ� �޼���.
//        components.push_back(component);
//    } 
//    void RemoveComponent(Component* component) { // Object���� Component�� �����ϴ� �޼���.
//        components.erase(std::remove(components.begin(), components.end(), component), components.end());
//        delete component; // Component �޸� ����
//    } 
//
//    void Render() {// Object�� �׸��� �޼���.
//        for (Component* component : components) {
//            component->Render(); // �� Component�� Render �޼��� ȣ��
//        }
//    } 
//    
//
//};