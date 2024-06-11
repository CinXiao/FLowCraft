#pragma once
#include<QObject>
#include<QMetaType>
#include<QFile>
#include<QString>
namespace Globe {
	struct Vector_Type
	{
		QList<float> data;
		// 加法
		Vector_Type operator+(const Vector_Type& other) const {
			Vector_Type result;
			for (int i = 0; i < data.size(); ++i) {
				result.data.append(data[i] + other.data[i]);
			}
			return result;
		}
		// 减法
		Vector_Type operator-(const Vector_Type& other) const {
			Vector_Type result;
			for (int i = 0; i < data.size(); ++i) {
				result.data.append(data[i] - other.data[i]);
			}
			return result;
		}
		// 向量叉乘运算符
		Vector_Type operator*(const Vector_Type& other) const {
			Vector_Type result;
			if (data.size() != 3 || other.data.size() != 3) {
				// 向量叉积只在三维空间中定义
				// 如果不是三维向量，返回空向量
				return result;
			}
			result.data.append(data[1] * other.data[2] - data[2] * other.data[1]); // i
			result.data.append(data[2] * other.data[0] - data[0] * other.data[2]); // j
			result.data.append(data[0] * other.data[1] - data[1] * other.data[0]); // k
			return result;
		}


	};
	Q_DECLARE_METATYPE(Vector_Type)

		struct Matrix_Type
	{
		QList<Vector_Type> data;
		// 添加矩阵加法
		Matrix_Type operator+(const Matrix_Type& other) const {
			Matrix_Type result;
			for (int i = 0; i < data.size(); ++i) {
				Vector_Type row;
				for (int j = 0; j < data[i].data.size(); ++j) {
					row.data.append(data[i].data[j] + other.data[i].data[j]);
				}
				result.data.append(row);
			}
			return result;
		}
		// 添加矩阵减法
		Matrix_Type operator-(const Matrix_Type& other) const {
			Matrix_Type result;
			for (int i = 0; i < data.size(); ++i) {
				Vector_Type row;
				for (int j = 0; j < data[i].data.size(); ++j) {
					row.data.append(data[i].data[j] - other.data[i].data[j]);
				}
				result.data.append(row);
			}
			return result;
		}

		// 矩阵乘以标量
		Matrix_Type operator*(float scalar) const {
			Matrix_Type result;
			for (int i = 0; i < data.size(); ++i) {
				Vector_Type row;
				for (int j = 0; j < data[i].data.size(); ++j) {
					row.data.append(data[i].data[j] * scalar);
				}
				result.data.append(row);
			}
			return result;
		}
		// 矩阵转置
		Matrix_Type transpose() const {
			Matrix_Type result;
			// 如果矩阵为空，则返回空矩阵
			if (data.isEmpty()) {
				return result;
			}
			int numRows = data.size();
			int numCols = data[0].data.size();
			// 初始化转置矩阵的尺寸
			result.data.resize(numCols);
			for (int i = 0; i < numCols; ++i) {
				result.data[i].data.resize(numRows);
			}
			// 执行转置操作
			for (int i = 0; i < numRows; ++i) {
				for (int j = 0; j < numCols; ++j) {
					result.data[j].data[i] = data[i].data[j];
				}
			}
			return result;
		}

		// 重载矩阵乘法运算符
		Matrix_Type operator*(const Matrix_Type& other) const {
			Matrix_Type result;
			// 检查矩阵的尺寸是否满足乘法条件
			if (data.isEmpty() || data[0].data.size() != other.data.size()) {
				// 如果左矩阵的列数不等于右矩阵的行数，则无法进行矩阵乘法，返回空矩阵
				return result;
			}
			// 计算结果矩阵的尺寸
			int resultRows = data.size();
			int resultCols = other.data[0].data.size();
			// 初始化结果矩阵
			result.data.resize(resultRows);
			for (int i = 0; i < resultRows; ++i) {
				result.data[i].data.resize(resultCols);
			}
			// 执行矩阵乘法
			for (int i = 0; i < resultRows; ++i) {
				for (int j = 0; j < resultCols; ++j) {
					float sum = 0.0;
					for (int k = 0; k < data[0].data.size(); ++k) {
						sum += data[i].data[k] * other.data[k].data[j];
					}
					result.data[i].data[j] = sum;
				}
			}
			return result;
		}


	};
	Q_DECLARE_METATYPE(Matrix_Type)

}
