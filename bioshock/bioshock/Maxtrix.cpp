#include "Matrix.h"

mat2::mat2(vec2 _row1, vec2 _row2)
{
	//Sets row1 and row2
	row1 = _row1;
	row2 = _row2;
}

void mat2::Add(mat2 m)
{
	//adds the passed parameter to THIS matrix 
	this->row1 = this->row1 + m.row1;
	this->row2 = this->row2 + m.row2;
}

void mat2::Subtract(mat2 m)
{
	//Subtracts the passed paramater from THIS matrix 
	this->row1 = this->row1 - m.row1;
	this->row2 = this->row2 - m.row2;
}

void mat2::Print()
{
	//Prints out formatted matrix in console 
	std::cout << "[ " << this->row1.x << ", " << this->row1.y << " ]\n";
	std::cout << "[ " << this->row2.x << ", " << this->row2.y << " ]\n";
}

mat2 mat2::Transpose()
{
	//Just swaps the rows and coloums within the maxtrix 
	mat2 temp;
	temp.row1 = vec2(row1.x, row2.x);
	temp.row2 = vec2(row1.y, row2.y);


	return temp;
}

float mat2::Determinant()
{
	float temp = (row1.x * row2.y) - (row1.y * row2.x);
	return temp;
}

mat2 mat2::Inverse()
{
	//The inverse is equal to this 
	//  -1    =      1
	//[A B]   =  ----------[ D -B]
	//[C D]   =  Det(mat2) [-C  A]

	//get one over determinate 
	float oneOverDet = 1.f / Determinant();

	//creates new matrix to be multiplied 
	mat2 temp = mat2(
		vec2(row2.y, -row1.y),
		vec2(-row2.x, row2.x)
	);

	//multiplies temp by 1 over det 
	temp = temp * oneOverDet;

	return temp;
}

mat2 mat2::operator+(mat2 m)
{
	//returns the summed matrix 
	return mat2(this->row1 + m.row1, this->row2 + m.row2);
}

mat2 mat2::operator-(mat2 m)
{
	//returns the difference
	return mat2(this->row1 - m.row1, this->row2 - m.row2);
}

mat2 mat2::operator*(float f)
{
	//returns product
	return mat2(this->row1 * f, this->row2 * f);
}

mat2 mat2::operator*(mat2 m)
{
	vec2 mCol1 = vec2(m.row1.x, m.row2.x);
	vec2 mCol2 = vec2(m.row1.y, m.row2.y);

	mat2 temp = mat2(
		vec2(row1.Dot(mCol1), row1.Dot(mCol2)),
		vec2(row2.Dot(mCol1), row2.Dot(mCol2))
	);

	return temp;
}

vec2 mat2::operator*(vec2 v)
{
	//Mutliplies 2X2 matrix by 2D vector 
	vec2 temp = vec2(
		row1.x * v.x + row1.y * v.y,
		row2.x * v.x + row2.y * v.y
	);

	return temp;
}

vec2 mat2::operator[](int i)
{
	//Indexes variables at i 
	//* 0 = row1
	//* 1 = row2
	return *hold[i];
}

mat3::mat3(vec3 _row1, vec3 _row2, vec3 _row3)
{
	//Sets row1, row2, and row3
	row1 = _row1;
	row2 = _row2;
	row3 = _row3;
}

mat3::mat3(mat4 m)
{
	//creates a 3x3 matrix with a 4x4 matrix 
	this->row1 = vec3(m.row1.x, m.row1.y, m.row1.z);
	this->row2 = vec3(m.row2.x, m.row2.y, m.row2.z);
	this->row3 = vec3(m.row3.x, m.row3.y, m.row3.z);
}

mat3 mat3::Transpose(mat3 R)
{
	//just swaps the rows and colummns within the matrix 
	mat3 temp;
	temp.row1 = vec3(R.row1.x, R.row1.y, R.row1.z);
	temp.row2 = vec3(R.row2.x, R.row2.y, R.row2.z);
	temp.row3 = vec3(R.row3.x, R.row3.y, R.row3.z);

	//return transposed matrix 
	return temp;
}

void mat3::Add(mat3 m)
{
	//adds the passed parameter to THIS matrix 
	this->row1 = this->row1 + m.row1;
	this->row2 = this->row2 + m.row2;
	this->row3 = this->row3 + m.row3;
}

void mat3::Subtract(mat3 m)
{
	//Subtracts the passed parameter from THIS matrix 
	this->row1 = this->row1 - m.row1;
	this->row2 = this->row2 - m.row2;
	this->row3 = this->row3 - m.row3;
}

void mat3::Print()
{
	//Prints out formatted matrix in console 
	std::cout << "[ " << this->row1.x << ", " << this->row1.y << ", " << this->row1.z << " ]\n";
	std::cout << "[ " << this->row2.x << ", " << this->row2.y << ", " << this->row2.z << " ]\n";
	std::cout << "[ " << this->row3.x << ", " << this->row3.y << ", " << this->row3.z << " ]\n";
}

mat3 mat3::Transpose()
{
	//just swaps the rows and colummns within the matrix 
	mat3 temp;
	temp.row1 = vec3(row1.x, row2.x, row3.x);
	temp.row2 = vec3(row1.y, row2.y, row3.y);
	temp.row3 = vec3(row1.z, row2.z, row3.z);

	//return transposed matrix 
	return temp;
}

float mat3::Determinant()
{
	//returns the determinant 
	//first term 
	mat2 tempMat(vec2(row2.y, row2.z), vec2(row3.y, row3.z));
	float temp = row1.x * tempMat.Determinant();
	//second term
	tempMat = mat2(vec2(row2.x, row2.z), vec2(row3.x, row3.z));
	temp -= row1.y * tempMat.Determinant();
	//third term 
	tempMat = mat2(vec2(row2.x, row2.y), vec2(row3.x, row3.y));
	temp += row1.z * tempMat.Determinant();

	//return the result 
	return temp;
}

mat3 mat3::Adjugate()
{
	//the transposed matrix of the matrix we're adjugating
	mat3 thisT = this->Transpose();

	//make the first row 
	mat2 firstTempMat2(vec2(thisT.row2.y, thisT.row2.z), vec2(thisT.row3.y, thisT.row3.z)); //det = x
	mat2 secondTempMat2(vec2(thisT.row2.x, thisT.row2.z), vec2(thisT.row3.x, thisT.row3.z)); //-1 * det = y
	mat2 thirdTempMat2(vec2(thisT.row2.x, thisT.row2.y), vec2(thisT.row3.x, thisT.row3.y)); //det = z
	vec3 tempRow1 = vec3(firstTempMat2.Determinant(), -1 * secondTempMat2.Determinant(), thirdTempMat2.Determinant()); // first row 

	//make the second row 
	firstTempMat2 = mat2(vec2(thisT.row1.y, thisT.row1.z), vec2(thisT.row3.y, thisT.row3.z)); //-1 * det = x
	secondTempMat2 = mat2(vec2(thisT.row1.x, thisT.row1.z), vec2(thisT.row3.x, thisT.row3.z)); //det = y
	thirdTempMat2 = mat2(vec2(thisT.row1.x, thisT.row1.y), vec2(thisT.row3.x, thisT.row3.y)); //-1 * det = z
	vec3 tempRow2 = vec3(-1 * firstTempMat2.Determinant(), secondTempMat2.Determinant(), -1 * thirdTempMat2.Determinant()); //Second row 

	//make the third row 
	firstTempMat2 = mat2(vec2(thisT.row1.y, thisT.row1.z), vec2(thisT.row2.y, thisT.row2.z)); //det = x
	secondTempMat2 = mat2(vec2(thisT.row1.x, thisT.row1.z), vec2(thisT.row2.x, thisT.row2.z)); //-1 * det = y
	thirdTempMat2 = mat2(vec2(thisT.row1.x, thisT.row1.y), vec2(thisT.row2.x, thisT.row2.y)); //det = z
	vec3 tempRow3 = vec3(firstTempMat2.Determinant(), -1 * secondTempMat2.Determinant(), thirdTempMat2.Determinant()); //Third row 

	//Combine the 3 rows into a matrix and return it 
	return mat3(tempRow1, tempRow2, tempRow3);
}

mat3 mat3::Inverse()
{
	//          1
	//M^-1 = -------- * Adj(M) 
	//        det(M)

	//caluclate 1 over the determinate 
	float temp = 1.f / this->Determinant();

	//return that times the adjugate 
	return this->Adjugate() * temp;
}

mat3 mat3::operator-()
{
	//negates all the rows
	return mat3(-row1, -row2, -row3);
}

mat3 mat3::operator+(mat3 m)
{
	//returns the summed matrix 
	return mat3(this->row1 + m.row1, this->row2 + m.row2, this->row3 + m.row3);
}

mat3 mat3::operator-(mat3 m)
{
	//returns the difference
	return mat3(this->row1 - m.row1, this->row2 - m.row2, this->row3 - m.row3);
}

vec3 mat3::operator[](int i)
{
	//indexes the variables at i 
	return *hold[i];
}

vec3 mat3::operator*(vec3 vec)
{
	//multiples a 3X3 matrix by a 3D vector 
	vec3 temp;
	temp = vec3(
		row1.x * vec.x + row1.y * vec.y + row1.z * vec.z,
		row2.x * vec.x + row2.y * vec.y + row2.z * vec.z,
		row3.x * vec.x + row3.y * vec.y + row3.z * vec.z
	);
	//returns the 3D vector 
	return temp;
}

mat3 mat3::operator*(mat3 m)
{
	vec3 mCol1 = vec3(m.row1.x, m.row2.x, m.row3.x);
	vec3 mCol2 = vec3(m.row1.y, m.row2.y, m.row3.y);
	vec3 mCol3 = vec3(m.row1.z, m.row2.z, m.row3.z);

	mat3 temp = mat3(
		vec3(row1.Dot(mCol1), row1.Dot(mCol2), row1.Dot(mCol3)),
		vec3(row2.Dot(mCol1), row2.Dot(mCol2), row2.Dot(mCol3)),
		vec3(row3.Dot(mCol1), row3.Dot(mCol2), row3.Dot(mCol3))
	);

	return temp;
}

mat3 mat3::operator*(float f)
{
	//returns product
	return mat3(this->row1 * f, this->row2 * f, this->row3 * f);
}


mat4::mat4(vec4 _row1, vec4 _row2, vec4 _row3, vec4 _row4)
{
	//Sets row1, row2, row3, and row4
	row1 = _row1;
	row2 = _row2;
	row3 = _row3;
	row4 = _row4;
}

mat4::mat4(mat3 rot, vec3 trans)
{
	//creates a homogenous transformation matrix using the rotation maxtrix and translation vector
	row1 = vec4(rot.row1.x, rot.row1.y, rot.row1.z, trans.x);
	row2 = vec4(rot.row2.x, rot.row2.y, rot.row2.z, trans.y);
	row3 = vec4(rot.row3.x, rot.row3.y, rot.row3.z, trans.z);
	row4 = vec4(0.f, 0.f, 0.f, 1.f);
}

void mat4::Add(mat4 m)
{
	//adds the passed parameter to THIS matrix 
	this->row1 = this->row1 + m.row1;
	this->row2 = this->row2 + m.row2;
	this->row3 = this->row3 + m.row3;
	this->row4 = this->row4 + m.row4;
}

void mat4::Subtract(mat4 m)
{
	//subtracts the passed parameter frpm THIS matrix 
	this->row1 = this->row1 - m.row1;
	this->row2 = this->row2 - m.row2;
	this->row3 = this->row3 - m.row3;
	this->row4 = this->row4 - m.row4;
}

void mat4::Print()
{
	//Prints out formatted matrix in console 
	std::cout << "[ " << this->row1.x << ", " << this->row1.y << ", " << this->row1.z << ", " << this->row1.w << " ]\n";
	std::cout << "[ " << this->row2.x << ", " << this->row2.y << ", " << this->row2.z << ", " << this->row2.w << " ]\n";
	std::cout << "[ " << this->row3.x << ", " << this->row3.y << ", " << this->row3.z << ", " << this->row3.w << " ]\n";
	std::cout << "[ " << this->row4.x << ", " << this->row4.y << ", " << this->row4.z << ", " << this->row4.w << " ]\n";
}

mat4 mat4::Transpose()
{
	//just swaps the rows and colummns within the matrix 
	mat4 temp;
	temp.row1 = vec4(row1.x, row2.x, row3.x, row4.x);
	temp.row2 = vec4(row1.y, row2.y, row3.y, row4.y);
	temp.row3 = vec4(row1.z, row2.z, row3.z, row4.z);
	temp.row4 = vec4(row1.w, row2.w, row3.w, row4.w);

	//return transposed matrix 
	return temp;
}

float mat4::Determinant()
{
	//returns the determinant 
	//first term 
	mat3 tempMat(vec3(row2.y, row2.z, row2.w), vec3(row3.y, row3.z, row3.w), vec3(row4.y, row4.z, row4.w));
	float temp = row1.x * tempMat.Determinant();
	//second term
	tempMat = mat3(vec3(row2.x, row2.z, row2.w), vec3(row3.x, row3.z, row3.w), vec3(row4.x, row4.z, row4.w));
	temp -= row1.y * tempMat.Determinant();
	//third term 
	tempMat = mat3(vec3(row2.x, row2.y, row2.w), vec3(row3.x, row3.y, row3.w), vec3(row4.x, row4.y, row4.w));
	temp += row1.z * tempMat.Determinant();
	//forth term 
	tempMat = mat3(vec3(row2.x, row2.y, row2.z), vec3(row3.x, row3.y, row3.z), vec3(row4.x, row4.y, row4.z));
	temp -= row1.w * tempMat.Determinant();


	//return the result 
	return temp;
}

mat4 mat4::Adjugate()
{
	//the transposed matrix of the matrix we're adjugating
	mat4 thisT = this->Transpose();

	//make the first row 
	mat3 firstTempMat(vec3(thisT.row2.y, thisT.row2.z, thisT.row2.w), vec3(thisT.row3.y, thisT.row3.z, thisT.row3.w), vec3(thisT.row4.y, thisT.row4.z, thisT.row4.w)); //det = x
	mat3 secondTempMat(vec3(thisT.row2.x, thisT.row2.z, thisT.row2.w), vec3(thisT.row3.x, thisT.row3.z, thisT.row3.w), vec3(thisT.row4.x, thisT.row4.z, thisT.row4.w)); //-1 * det = y
	mat3 thirdTempMat(vec3(thisT.row2.x, thisT.row2.y, thisT.row2.w), vec3(thisT.row3.x, thisT.row3.y, thisT.row3.w), vec3(thisT.row4.x, thisT.row4.y, thisT.row4.w)); //det = z
	mat3 forthTempMat(vec3(thisT.row2.x, thisT.row2.y, thisT.row2.z), vec3(thisT.row3.x, thisT.row3.y, thisT.row3.z), vec3(thisT.row4.x, thisT.row4.y, thisT.row4.z)); //-1 * det = w
	vec4 tempRow1 = vec4(firstTempMat.Determinant(), -1 * secondTempMat.Determinant(), thirdTempMat.Determinant(), -1 * forthTempMat.Determinant()); // first row 

	//make the second row 
	firstTempMat = mat3(vec3(thisT.row1.y, thisT.row1.z, thisT.row1.w), vec3(thisT.row3.y, thisT.row3.z, thisT.row3.w), vec3(thisT.row4.y, thisT.row4.z, thisT.row4.w)); //-1 * det = x
	secondTempMat = mat3(vec3(thisT.row1.x, thisT.row1.z, thisT.row1.w), vec3(thisT.row3.x, thisT.row3.z, thisT.row3.w), vec3(thisT.row4.x, thisT.row4.z, thisT.row4.w)); //det = y
	thirdTempMat = mat3(vec3(thisT.row1.x, thisT.row1.y, thisT.row1.w), vec3(thisT.row3.x, thisT.row3.y, thisT.row3.w), vec3(thisT.row4.x, thisT.row4.y, thisT.row4.w)); //-1 * det = z
	forthTempMat = mat3(vec3(thisT.row1.x, thisT.row1.y, thisT.row1.z), vec3(thisT.row3.x, thisT.row3.y, thisT.row3.z), vec3(thisT.row4.x, thisT.row4.y, thisT.row4.z)); //det = w
	vec4 tempRow2 = vec4(-1 * firstTempMat.Determinant(), secondTempMat.Determinant(), -1 * thirdTempMat.Determinant(), forthTempMat.Determinant()); //Second row 

	//make the third row 
	firstTempMat = mat3(vec3(thisT.row1.y, thisT.row1.z, thisT.row1.w), vec3(thisT.row2.y, thisT.row2.z, thisT.row2.w), vec3(thisT.row4.y, thisT.row4.z, thisT.row4.w)); //det = x
	secondTempMat = mat3(vec3(thisT.row1.x, thisT.row1.z, thisT.row1.w), vec3(thisT.row2.x, thisT.row2.z, thisT.row2.w), vec3(thisT.row4.x, thisT.row4.z, thisT.row4.w)); //-1 * det = y
	thirdTempMat = mat3(vec3(thisT.row1.x, thisT.row1.y, thisT.row1.w), vec3(thisT.row2.x, thisT.row2.y, thisT.row2.w), vec3(thisT.row4.x, thisT.row4.y, thisT.row4.w)); //det = z
	forthTempMat = mat3(vec3(thisT.row1.x, thisT.row1.y, thisT.row1.z), vec3(thisT.row2.x, thisT.row2.y, thisT.row2.z), vec3(thisT.row4.x, thisT.row4.y, thisT.row4.z)); //-1 * det = w
	vec4 tempRow3 = vec4(firstTempMat.Determinant(), -1 * secondTempMat.Determinant(), thirdTempMat.Determinant(), -1 * forthTempMat.Determinant()); //Third row 

	//make the forth row 
	firstTempMat = mat3(vec3(thisT.row1.y, thisT.row1.z, thisT.row1.w), vec3(thisT.row2.y, thisT.row2.z, thisT.row2.w), vec3(thisT.row3.y, thisT.row3.z, thisT.row3.w)); //-1 * det = x
	secondTempMat = mat3(vec3(thisT.row1.x, thisT.row1.z, thisT.row1.w), vec3(thisT.row2.x, thisT.row2.z, thisT.row2.w), vec3(thisT.row3.x, thisT.row3.z, thisT.row3.w)); //det = y
	thirdTempMat = mat3(vec3(thisT.row1.x, thisT.row1.y, thisT.row1.w), vec3(thisT.row2.x, thisT.row2.y, thisT.row2.w), vec3(thisT.row3.x, thisT.row3.y, thisT.row3.w)); //-1 * det = z
	forthTempMat = mat3(vec3(thisT.row1.x, thisT.row1.y, thisT.row1.z), vec3(thisT.row2.x, thisT.row2.y, thisT.row2.z), vec3(thisT.row3.x, thisT.row3.y, thisT.row3.z)); //det = w
	vec4 tempRow4 = vec4(-1 * firstTempMat.Determinant(), secondTempMat.Determinant(), -1 * thirdTempMat.Determinant(), forthTempMat.Determinant()); //Forth row 

	//Combine the 4 rows into a matrix and return it 
	return mat4(tempRow1, tempRow2, tempRow3, tempRow4);
}

mat4 mat4::Inverse()
{
	//          1
	//M^-1 = -------- * Adj(M) 
	//        det(M)

		//caluclate 1 over the determinate 
	float temp = 1.f / this->Determinant();

	//return that times the adjugate 
	return this->Adjugate() * temp;
}

mat4 mat4::FastInverse(mat4 mat)
{
	//in order to do a faster inverse we assume it's a homogenous transformation matrix which means 
	//| R(3X3) | T(1X3) | inverse is equal to | R(3X3)^T|T(1X3)*-R|
	//|--------|--------|                     |---------|---------|
	//| 0(3X3) | 1(1X1) |                     |  0(3X3) |  1(1X1) |

	//grab a reference to the rotation matrix 
	mat3 rotation = mat3(mat);
	//grab the translation maxtrix out of mat
	vec3 translation = Translation(mat);
	//Transpose rotation matrix 
	rotation = mat3::Transpose(rotation);
	//Multiply negative rotation by translation 
	translation = -rotation * translation;

	//recreate homogenous transformation matrix using the new 3X3 rotation matrix and 3D transalation vector 
	return mat4(rotation, translation);
}

vec3 mat4::Translation(mat4 mat)
{
	//grabs the translation data from the homogenous transformation matrix 
	return vec3(mat.row1.z, mat.row2.z, mat.row3.z);
}

mat4 mat4::operator+(mat4 m)
{
	//returns the summed matrix 
	return mat4(this->row1 + m.row1, this->row2 + m.row2, this->row3 + m.row3, this->row4 + m.row4);
}

mat4 mat4::operator-(mat4 m)
{
	//returns the difference
	return mat4(this->row1 - m.row1, this->row2 - m.row2, this->row3 - m.row3, this->row4 - m.row4);
}

mat4 mat4::operator*(float f)
{
	//returns product
	return mat4(this->row1 * f, this->row2 * f, this->row3 * f, this->row4 * f);
}

mat4 mat4::operator*(mat4 m)
{
	vec4 mCol1 = vec4(m.row1.x, m.row2.x, m.row3.x, m.row4.x);
	vec4 mCol2 = vec4(m.row1.y, m.row2.y, m.row3.y, m.row4.y);
	vec4 mCol3 = vec4(m.row1.z, m.row2.z, m.row3.z, m.row4.z);
	vec4 mCol4 = vec4(m.row1.w, m.row2.w, m.row3.w, m.row4.w);

	mat4 temp = mat4(
		vec4(row1.Dot(mCol1), row1.Dot(mCol2), row1.Dot(mCol3), row1.Dot(mCol4)),
		vec4(row2.Dot(mCol1), row2.Dot(mCol2), row2.Dot(mCol3), row2.Dot(mCol4)),
		vec4(row3.Dot(mCol1), row3.Dot(mCol2), row3.Dot(mCol3), row3.Dot(mCol4)),
		vec4(row4.Dot(mCol1), row4.Dot(mCol2), row4.Dot(mCol3), row4.Dot(mCol4))
	);

	return temp;
}

vec4 mat4::operator*(vec4 v)
{
	//multiples a 4X4 matrix by a 4D vector 
	vec4 temp;
	temp = vec4(
		row1.x * v.x + row1.y * v.y + row1.z * v.z + row1.w * v.w,
		row2.x * v.x + row2.y * v.y + row2.z * v.z + row2.w * v.w,
		row3.x * v.x + row3.y * v.y + row3.z * v.z + row3.w * v.w,
		row4.x + v.x + row4.y + v.y + row4.z + v.z + row4.w * v.w
	);
	//returns the 4D vector 
	return temp;
}

vec4 mat4::operator[](int i)
{
	//Indexes the variables at i 
	return *hold[i];
}
