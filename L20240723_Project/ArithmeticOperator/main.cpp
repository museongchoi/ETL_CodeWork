#include <iostream> // ǥ�� ���
// "iostream" �ڽ��� �ۼ��� �������
using namespace std;	// ���, �̸� ����, std Ŭ���� �ȿ� ����� ���

// entry point - ���� ����Ʈ
// main �Լ� ��ȯ�� int, ��ȯ���� 0 / main �� �ϳ�, main ������ ó�� ���� ��
int main()
{
	// ��� const : ������ �ʴ� ��
	cout << 1 << "\n"; // ������
	cout << 1.1f << endl; // f �Ǽ���

	// ��Ģ ����
	cout << 1 + 1 << "\n";
	cout << 1 * 1 << "\n";
	cout << 1 / 1 << "\n";
	cout << 1 % 1 << "\n";

	// ���� ���� - �޸� ������ ��ġ ������ ���� �ϴ� �̸��� ���� ���� ����. + ������ ������ Ÿ��
	// �Ľ�Į ���̽� - �𸮾� ��Ÿ�� ù ���� �빮�� ���� ù���� �빮��

	// �޸� ��򰡿� �� 4byte ������ ���� - 2�� 64�� (64��Ʈ)
	int MyMoney; // ����
	MyMoney = 10; // �ʱ�ȭ
	int MyGold = 100; // ���� + �ʱ�ȭ

	cout << MyMoney << "\n";

	int HP = 0;
	int Damage = 0;
	int Gold = 0;

	HP = 100;
	Damage = 10;
	Gold = 1;

	// ����
	cout << HP - Damage << "\n";

	// ��
	cout << HP + Damage << "\n";
	cout << &HP << "\n"; // & - �ּҰ�

	// ���� ���̶� ������
	// ���� ���� ���ϸ�

	return 0;
}