#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestAddElement)
		{
			SparseMatrix<int> m(3, 3);
			m.addElement(1, 1, 1);
			m.addElement(2, 2, 2);
			m.addElement(3, 3, 3);
			Assert::AreEqual(1, m.getValueAt(1, 1));
			Assert::AreEqual(2, m.getValueAt(2, 2));
			Assert::AreEqual(3, m.getValueAt(3, 3));
			Assert::AreEqual(0, m.getValueAt(1, 2));
		}
		TEST_METHOD(TestPrint)
		{
			SparseMatrix<int> m(3, 3);
			m.addElement(1, 1, 1);
			m.addElement(2, 2, 2);
			m.addElement(3, 3, 3);
			std::stringstream ss;
			m.print(ss);
			Assert::AreEqual(std::string("1\t0\t0\t\n0\t2\t0\t\n0\t0\t3\t\n"), ss.str());
		}
		TEST_METHOD(TestAdd)
		{
			SparseMatrix<int> m1(3, 3);
			m1.addElement(1, 1, 1);
			m1.addElement(2, 2, 2);
			m1.addElement(3, 3, 3);
			SparseMatrix<int> m2(3, 3);
			m2.addElement(1, 1, 4);
			m2.addElement(2, 2, 5);
			m2.addElement(3, 3, 6);
			SparseMatrix<int> m3 = m1 + m2;
			Assert::AreEqual(5, m3.getValueAt(1, 1));
			Assert::AreEqual(7, m3.getValueAt(2, 2));
			Assert::AreEqual(9, m3.getValueAt(3, 3));
		}
		TEST_METHOD(TestSubstraction)
		{
			SparseMatrix<int> m1(3, 3);
			m1.addElement(1, 1, 1);
			m1.addElement(2, 2, 2);
			m1.addElement(3, 3, 3);
			SparseMatrix<int> m2(3, 3);
			m2.addElement(1, 1, 4);
			m2.addElement(2, 2, 5);
			m2.addElement(3, 3, 6);
			SparseMatrix<int> m3 = m1 - m2;
			Assert::AreEqual(-3, m3.getValueAt(1, 1));
			Assert::AreEqual(-3, m3.getValueAt(2, 2));
			Assert::AreEqual(-3, m3.getValueAt(3, 3));
		}
		TEST_METHOD(TestMultiply)
		{
			SparseMatrix<int> m1(3, 3);
			m1.addElement(1, 1, 1);
			m1.addElement(2, 2, 2);
			m1.addElement(3, 3, 3);
			SparseMatrix<int> m2(3, 3);
			m2.addElement(1, 1, 4);
			m2.addElement(2, 2, 5);
			m2.addElement(3, 3, 6);
			SparseMatrix<int> m3 = m1 * m2;
			Assert::AreEqual(4, m3.getValueAt(1, 1));
			Assert::AreEqual(10, m3.getValueAt(2, 2));
			Assert::AreEqual(18, m3.getValueAt(3, 3));
		}
		TEST_METHOD(TestMultiplyByScalar)
		{
			SparseMatrix<int> m1(3, 3);
			m1.addElement(1, 1, 1);
			m1.addElement(2, 2, 2);
			m1.addElement(3, 3, 3);
			SparseMatrix<int> m2 = m1 * 2;
			Assert::AreEqual(2, m2.getValueAt(1, 1));
			Assert::AreEqual(4, m2.getValueAt(2, 2));
			Assert::AreEqual(6, m2.getValueAt(3, 3));
		}

	};
}
