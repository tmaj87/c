//for bones
typedef float matrix3x4_t[3][4];
matrix3x4_t boneMatrix[39]; //for all bones except the fingers

//for coordinates
struct Vec3
{
public:
    float x;
    float y;
    float z;
	Vec3() {}
	Vec3(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}
};

//bone id's for players
enum eBones 
{ 
    Bone_Pelvis = 0, 
    Bone_Spine_1 = 1, 
    Bone_Spine_2 = 2, 
    Bone_Spine_3 = 3, 
    Bone_Spine_4 = 4, 
    Bone_Neck = 5, 
    Bone_Left_Clavicle = 6, 
    Bone_Left_UpperArm = 7, 
    Bone_Left_ForeArm = 8, 
    Bone_Left_Hand = 9, 
    Bone_Head = 10, 
    Bone_forward = 11, 
    Bone_Right_Clavicle = 12, 
    Bone_Right_UpperArm = 13, 
    Bone_Right_ForeArm = 14, 
    Bone_Right_Hand = 15, 
    Bone_weapon = 16, 
    Bone_weapon_slide = 17, 
    Bone_weapon_Right_Hand = 18, 
    Bone_weapon_Left_Hand = 19, 
    Bone_weapon_Clip1 = 20, 
    Bone_weapon_Clip2 = 21, 
    Bone_silencer = 22, // added last patch 
    Bone_Right_Thigh = 23,
    Bone_Right_Calf = 24,
    Bone_Right_Foot = 25,
    Bone_Left_Thigh = 26,
    Bone_Left_Calf = 27,
    Bone_Left_Foot = 28,
    Bone_Left_ForeTwist = 29,
    Bone_Left_CalfTwist = 30,
    Bone_Right_CalfTwist = 31,
    Bone_Left_ThighTwist = 32,
    Bone_Right_ThighTwist = 33,
    Bone_Left_UpArmTwist = 34,
    Bone_Right_UpArmTwist = 35,
    Bone_Right_ForeTwist = 36,
    Bone_Right_Toe = 37,
    Bone_Left_Toe = 38,
    Bone_Right_Finger01 = 39,
    Bone_Right_Finger02 = 40, 
    Bone_Right_Finger03 = 41, 
    Bone_Right_Finger04 = 42, 
    Bone_Right_Finger05 = 43, 
    Bone_Right_Finger06 = 44, 
    Bone_Right_Finger07 = 45, 
    Bone_Right_Finger08 = 46, 
    Bone_Right_Finger09 = 47, 
    Bone_Right_Finger10 = 48, 
    Bone_Right_Finger11 = 49, 
    Bone_Right_Finger12 = 50, 
    Bone_Right_Finger13 = 51, 
    Bone_Right_Finger14 = 52, 
    Bone_Left_Finger01 = 53, 
    Bone_Left_Finger02 = 54, 
    Bone_Left_Finger03 = 55, 
    Bone_Left_Finger04 = 56, 
    Bone_Left_Finger05 = 57, 
    Bone_Left_Finger06 = 58, 
    Bone_Left_Finger07 = 59, 
    Bone_Left_Finger08 = 60, 
    Bone_Left_Finger09 = 61, 
    Bone_Left_Finger10 = 62, 
    Bone_Left_Finger11 = 63, 
    Bone_Left_Finger12 = 64, 
    Bone_Left_Finger13 = 65, 
    Bone_Left_Finger14 = 66, 
    Bone_Left_Finger15 = 67, 
    Bone_Right_Finger15 = 68
};  

struct HitBox
{
	Vec3 bbmin;
	Vec3 bbmax;
};
class HitBoxes
{
public:
	HitBox Pelvis;
	HitBox L_Thigh, L_Calf, L_Foot;
	HitBox R_Thigh, R_Calf, R_Foot;
	HitBox Spine2, Spine3, Spine4, Neck1, Head1;
	HitBox L_UpperArm, L_Forearm, L_Hand;
	HitBox R_UpperArm, R_Forearm, R_Hand;

	HitBoxes()
	{
		Pelvis.bbmin = Vec3(-6.420, -4.280, -6.955);
		Pelvis.bbmax = Vec3(4.280, 4.280, 6.955);
		
		L_Thigh.bbmin = Vec3(5.029, -3.959, -2.140);
		L_Thigh.bbmax = Vec3(22.149, 3.424, 4.280);

		L_Calf.bbmin = Vec3(2.675, -3.210, -2.247);
		L_Calf.bbmax = Vec3(19.260, 2.675, 2.247);

		L_Foot.bbmin = Vec3(2.943, -2.675, -2.408);
		L_Foot.bbmax = Vec3(6.688, 9.095, 2.408);

		R_Thigh.bbmin = Vec3(5.029, -3.959, -4.280);
		R_Thigh.bbmax = Vec3(22.149, 3.424, 2.140);

		R_Calf.bbmin = Vec3(5.029, -3.959, -4.280);
		R_Calf.bbmax = Vec3(22.149, 3.424, 2.140);

		R_Foot.bbmin = Vec3(2.943, -2.675, -2.408);
		R_Foot.bbmax = Vec3(6.688, 9.095, 2.408);

		Spine2.bbmin = Vec3(-4.280, -4.280, -5.885);
		Spine2.bbmax = Vec3(3.210, 5.350, 5.885);

		Spine3.bbmin = Vec3(-4.280, -4.280, -5.885);
		Spine3.bbmax = Vec3(3.210, 5.350, 5.885);

		Spine4.bbmin = Vec3(-4.280, -4.280, -5.885);
		Spine4.bbmax = Vec3(6.420, 5.350, 5.885);

		Neck1.bbmin = Vec3(-1.070, -2.622, -2.151);
		Neck1.bbmax = Vec3(3.103, 2.622, 2.151);

		Head1.bbmin = Vec3(-2.140, -3.745, -3.670);
		Head1.bbmax = Vec3(6.955, 3.745, 3.670);

		L_UpperArm.bbmin = Vec3(-2.675, -3.210, -2.140);
		L_UpperArm.bbmax = Vec3(12.840, 3.210, 2.140);

		L_Forearm.bbmin = Vec3(-0.000, -2.140, -2.140);
		L_Forearm.bbmax = Vec3(9.630, 2.140, 2.140);

		L_Hand.bbmin = Vec3(-1.723, -1.220, -1.380);
		L_Hand.bbmax = Vec3(4.473, 1.220, 1.380);

		R_UpperArm.bbmin = Vec3(-2.675, -3.210, -2.140);
		R_UpperArm.bbmax = Vec3(12.840, 3.210, 2.140);

		R_Forearm.bbmin = Vec3(-0.000, -2.140, -2.140);
		R_Forearm.bbmax = Vec3(9.630, 2.140, 2.140);
		
		R_Hand.bbmin = Vec3(-1.723, -1.220, -1.380);
		R_Hand.bbmax = Vec3(4.473, 1.220, 1.380);

	}
} hitboxes;

void BonePosition(const matrix3x4_t &boneMatrix, Vec3 &position)
{
	position.x = boneMatrix[0][3];
	position.y = boneMatrix[1][3];
	position.z = boneMatrix[2][3];
}

float DotProduct(Vec3 &v1, const float* v2)
{
	return v1.x*v2[0] + v1.y*v2[1] + v1.z*v2[2];
}

// transform in1 by the matrix in2
void VectorTransform (Vec3 &in1, const matrix3x4_t& in2, Vec3 &out)
{
	out.x = DotProduct(in1, in2[0]) + in2[0][3];
	out.y = DotProduct(in1, in2[1]) + in2[1][3];
	out.z = DotProduct(in1, in2[2]) + in2[2][3];
}

void GetHitBoxVectors(HitBox& hitBox, Vec3* hitBoxVectors, const eBones& bone)
{
	Vec3 points[] = { Vec3( hitBox.bbmin.x, hitBox.bbmin.y, hitBox.bbmin.z ),
	Vec3( hitBox.bbmin.x, hitBox.bbmax.y, hitBox.bbmin.z ),
	Vec3( hitBox.bbmax.x, hitBox.bbmax.y, hitBox.bbmin.z ),
	Vec3( hitBox.bbmax.x, hitBox.bbmin.y, hitBox.bbmin.z ),
	Vec3( hitBox.bbmax.x, hitBox.bbmax.y, hitBox.bbmax.z ),
	Vec3( hitBox.bbmin.x, hitBox.bbmax.y, hitBox.bbmax.z ),
	Vec3( hitBox.bbmin.x, hitBox.bbmin.y, hitBox.bbmax.z ),
	Vec3( hitBox.bbmax.x, hitBox.bbmin.y, hitBox.bbmax.z ) };

	for ( int index = 0; index < 8; ++index )
	{
		// scale down the hitbox size a tiny bit (default is a little too big)
		points[index].x *= 0.9;
		points[index].y *= 0.9;
		points[index].z *= 0.9;

		// transform the vector
		VectorTransform(points[index], boneMatrix[(int)bone], hitBoxVectors[index]);
	}
}

void DrawHitBox(Color& espColor, Vec3* hitBoxVectors, int ScreenWidth, int ScreenHeight)
{
	Vec3 startPosScreen, endPosScreen;
		//top of hit box
		for (int i  = 0; i < 3; i++)
		{
			ScreenTransform(worldToScreenMatrix, hitBoxVectors[i], startPosScreen, ScreenWidth, ScreenHeight);
			ScreenTransform(worldToScreenMatrix, hitBoxVectors[i + 1], endPosScreen, ScreenWidth, ScreenHeight);
			DrawLine(startPosScreen.x, startPosScreen.y, endPosScreen.x, endPosScreen.y, 1, espColor.r, espColor.g, espColor.b, 150);
		}
		ScreenTransform(worldToScreenMatrix, hitBoxVectors[0], startPosScreen, ScreenWidth, ScreenHeight);
		ScreenTransform(worldToScreenMatrix, hitBoxVectors[3], endPosScreen, ScreenWidth, ScreenHeight);
		DrawLine(startPosScreen.x, startPosScreen.y, endPosScreen.x, endPosScreen.y, 1, espColor.r, espColor.g, espColor.b, 150);

		//bottom of hit box
		for (int i  = 4; i < 7; i++)
		{
			ScreenTransform(worldToScreenMatrix, hitBoxVectors[i], startPosScreen, ScreenWidth, ScreenHeight);
			ScreenTransform(worldToScreenMatrix, hitBoxVectors[i + 1], endPosScreen, ScreenWidth, ScreenHeight);
			DrawLine(startPosScreen.x, startPosScreen.y, endPosScreen.x, endPosScreen.y, 1, espColor.r, espColor.g, espColor.b, 150);
		}
		ScreenTransform(worldToScreenMatrix, hitBoxVectors[4], startPosScreen, ScreenWidth, ScreenHeight);
		ScreenTransform(worldToScreenMatrix, hitBoxVectors[7], endPosScreen, ScreenWidth, ScreenHeight);
		DrawLine(startPosScreen.x, startPosScreen.y, endPosScreen.x, endPosScreen.y, 1, espColor.r, espColor.g, espColor.b, 150);
		
		//sides of hit box
		ScreenTransform(worldToScreenMatrix, hitBoxVectors[0], startPosScreen, ScreenWidth, ScreenHeight);
		ScreenTransform(worldToScreenMatrix, hitBoxVectors[6], endPosScreen, ScreenWidth, ScreenHeight);
		DrawLine(startPosScreen.x, startPosScreen.y, endPosScreen.x, endPosScreen.y, 1, espColor.r, espColor.g, espColor.b, 150);

		ScreenTransform(worldToScreenMatrix, hitBoxVectors[1], startPosScreen, ScreenWidth, ScreenHeight);
		ScreenTransform(worldToScreenMatrix, hitBoxVectors[5], endPosScreen, ScreenWidth, ScreenHeight);
		DrawLine(startPosScreen.x, startPosScreen.y, endPosScreen.x, endPosScreen.y, 1, espColor.r, espColor.g, espColor.b, 150);

		ScreenTransform(worldToScreenMatrix, hitBoxVectors[2], startPosScreen, ScreenWidth, ScreenHeight);
		ScreenTransform(worldToScreenMatrix, hitBoxVectors[4], endPosScreen, ScreenWidth, ScreenHeight);
		DrawLine(startPosScreen.x, startPosScreen.y, endPosScreen.x, endPosScreen.y, 1, espColor.r, espColor.g, espColor.b, 150);

		ScreenTransform(worldToScreenMatrix, hitBoxVectors[3], startPosScreen, ScreenWidth, ScreenHeight);
		ScreenTransform(worldToScreenMatrix, hitBoxVectors[7], endPosScreen, ScreenWidth, ScreenHeight);
		DrawLine(startPosScreen.x, startPosScreen.y, endPosScreen.x, endPosScreen.y, 1, espColor.r, espColor.g, espColor.b, 150);
}

void DrawESP(PlayerEntity& ourPlayer, PlayerEntity& theirPlayer, int ScreenWidth, int ScreenHeight)
{
	if (theirPlayer.boneMatrixPointer <= 0) return;
	//copy all bones into boneMatrix variable
	bool rslt = ReadProcessMemory(csgoHandle, (LPVOID)(theirPlayer.boneMatrixPointer), &boneMatrix, sizeof(boneMatrix), NULL);
	if (!rslt) return;

	Color espColor = GetESPColor(theirPlayer);

	if (espMode == ESPMode::Box)
	{
		...
	}
	else if (espMode == ESPMode::LegsOnly)
	{
		...
	}
	else if (espMode == ESPMode::SimpleSkeleton)
	{
		...
	}
	else if (espMode == ESPMode::FullSkeleton)
	{
		...
	}
	else if (espMode == ESPMode::HitBoxes)
	{
		Vec3 hitBoxVectors[8];
		//right hand
		GetHitBoxVectors(hitboxes.R_Hand, hitBoxVectors, eBones::Bone_Right_Hand);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//left hand
		GetHitBoxVectors(hitboxes.L_Hand, hitBoxVectors, eBones::Bone_Left_Hand);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//right foot
		GetHitBoxVectors(hitboxes.R_Foot, hitBoxVectors, eBones::Bone_Right_Foot);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//left foot
		GetHitBoxVectors(hitboxes.L_Foot, hitBoxVectors, eBones::Bone_Left_Foot);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//head
		GetHitBoxVectors(hitboxes.Head1, hitBoxVectors, eBones::Bone_Head);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//Pelvis
		GetHitBoxVectors(hitboxes.Pelvis, hitBoxVectors, eBones::Bone_Pelvis);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//right calf
		GetHitBoxVectors(hitboxes.R_Calf, hitBoxVectors, eBones::Bone_Right_Calf);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//left calf
		GetHitBoxVectors(hitboxes.L_Calf, hitBoxVectors, eBones::Bone_Left_Calf);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//right thigh
		GetHitBoxVectors(hitboxes.R_Thigh, hitBoxVectors, eBones::Bone_Right_Thigh);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//left thigh
		GetHitBoxVectors(hitboxes.L_Thigh, hitBoxVectors, eBones::Bone_Left_Thigh);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//spine 2
		GetHitBoxVectors(hitboxes.Spine2, hitBoxVectors, eBones::Bone_Spine_2);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//spine 3
		GetHitBoxVectors(hitboxes.Spine3, hitBoxVectors, eBones::Bone_Spine_3);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//spine 4
		GetHitBoxVectors(hitboxes.Spine4, hitBoxVectors, eBones::Bone_Spine_4);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//left forarm
		GetHitBoxVectors(hitboxes.L_Forearm, hitBoxVectors, eBones::Bone_Left_ForeArm);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//right forarm
		GetHitBoxVectors(hitboxes.R_Forearm, hitBoxVectors, eBones::Bone_Right_ForeArm);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//left upperarm
		GetHitBoxVectors(hitboxes.L_UpperArm, hitBoxVectors, eBones::Bone_Left_UpperArm);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//right upperarm
		GetHitBoxVectors(hitboxes.R_UpperArm, hitBoxVectors, eBones::Bone_Right_UpperArm);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);
		//neck
		GetHitBoxVectors(hitboxes.Neck1, hitBoxVectors, eBones::Bone_Neck);
		DrawHitBox(espColor, hitBoxVectors, ScreenWidth, ScreenHeight);

	}












/*
bool GetBonePosition(CBaseEntity* pPlayer, Vector& Hitbox, int Bone)
{
	matrix3x4 MatrixArray[128];

	if(!pPlayer->SetupBones( MatrixArray, 128, 0x00000100, g_pEngine->Time() ) )
		return FALSE;

	Hitbox = Vector(MatrixArray[Bone][0][3], MatrixArray[Bone][1][3], MatrixArray[Bone][2][3]);

	return true;
}
*/


/*
void DrawBone( int StartBone, int EndBone, CBaseEntity* target) {
	Vector StartBonePos, EndBonePos;
	Vector StartDrawPos, EndDrawPos;
	if(!target) {
		return;
	}

	GetBonePosition(target, StartBonePos, StartBone);
	GetBonePosition(target, EndBonePos, EndBone);

	if(!WorldToScreen(StartBonePos, StartDrawPos)) {
		return;
	}
	if(!WorldToScreen(EndBonePos, EndDrawPos)) {
		return;
	}

	g_pSurface->DrawSetColor(255, 0, 0, 255);
	g_pSurface->DrawLine(StartDrawPos.x, StartDrawPos.y, EndDrawPos.x, EndDrawPos.y);
}
*/

/*
void DrawBoneDebug(CBaseEntity* target, int boneNum) {
	Vector bonePos, boneScreenPos;

	GetBonePosition(target, bonePos, boneNum);

	if(!WorldToScreen(bonePos, boneScreenPos)) {
		return;
	}

	char buff[256];
	sprintf_s(buff, "%d", boneNum);
	g_pSurface->DrawSetColor(255, 0, 0, 255);
	g_pSurface->DrawOutlinedRect(boneScreenPos.x-5, boneScreenPos.y-5, boneScreenPos.x+5, boneScreenPos.y+5);
	DrawString(boneScreenPos.x, boneScreenPos.y, 255, buff);
}
*/



		/*
		for(int i = 0; i < 127; i++) {
			DrawBoneDebug(enemyPlayer, i);
		}
		*/

		/*
		static BYTE bones1[] = {33,21,9,12,36};
		static BYTE bones2[] = {6,0,9,0,3};
		for(int i = 0; i < 4; i++){    
			DrawBone(bones1[i], bones1[i+1], enemyPlayer);
		}
		for(int i = 0; i < 4; i++) {    
			DrawBone(bones2[i], bones2[i+1], enemyPlayer);
		}
		*/