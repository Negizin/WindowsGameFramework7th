#pragma once

#include<Windows.h>
#include<array>
#include <vector>
#include	"../../DrawObject/SkinMeshObject.h"
#include	"../../Material/PmxMaterialBase.h"
#include	"../Bone/MmdBone.h"
#include	"../../Vertex/Vertex.h"
#include "MeshLoader.h"

#ifdef UNICODE
typedef std::wstring pmxString;
typedef wchar_t pmxChar;
#else
typedef std::string pmxString;
typedef char pmxChar;
#endif

//------------------------------------------------------------
// �萔��`
//------------------------------------------------------------
const float PMX_MESH_SCALE = 1.0f;

class Pmx {
public:
#pragma pack(push,1)	//�A���C�������g������I�t

	/*!-----------------------------------------------------------
	//	@struct	PMXHeader
	------------------------------------------------------------*/
	struct Header {
		unsigned char	magic[4];
		float			version;
		//			�����܂Ń}�W�b�N�i���o�[
		unsigned char	variousDatasizeLength;		//�e��f�[�^�T�C�Y�̊i�[���@PMX��2.0�͂W�Œ�

		unsigned	char	encodeType;//0:UTF16 1:UTF8
		unsigned	char	appendUV;//�ǉ�UV
		unsigned	char	vertexIndexSize;//���_�C���f�b�N�X�̃f�[�^�T�C�Y
		unsigned	char	textureIndexSize;//�e�N�X�`���C���f�b�N�X�̃f�[�^�T�C�Y
		unsigned	char	materialIndexSize;//�}�e���A���C���f�b�N�X�̃f�[�^�T�C�Y
		unsigned	char	boneIndexSize;//�{�[���C���f�b�N�X�̃f�[�^�T�C�Y
		unsigned	char	morphIndexSize;//���[�t����ł������̃f�[�^�T�C�Y
		unsigned	char	rigidIndexSize;//���W�b�g�{�f�B�C���f�b�N�X�̃f�[�^�T�C�Y

		//���f�����
		unsigned	int	nameByteSize;				//���f�����T�C�Y
		pmxChar*	p_PmxName;						//���f����
		unsigned	int	nameEnglishByteSize;		//���f���p���T�C�Y
		pmxChar*	p_PmxNameEnglish;				//���f���p��
		unsigned	int	commentByteSize;				//�R�����g�T�C�Y
		pmxChar*	p_Comment;								//�R�����g
		unsigned	int	commentEnglishByteSize;		//�p��R�����g�T�C�Y
		pmxChar*	p_CommentEnglish;						//�p��R�����g
	};

	/*!-----------------------------------------------------------
	//	@struct	PMXVertex
	//	@brief	���_�f�[�^
	------------------------------------------------------------*/
	struct Vertex {
		enum {
			BDEF1,
			BDEF2,
			BDEF4,
			SDEF,
			QDEF,
		};
		float			pos[3];			///< ���_���W
		float			vNormal[3];		///< �@���x�N�g��
		float			uv[2];			///< �e�N�X�`�����W
		//�E�F�C�g�ό`����
		unsigned char weighttype;		//0: BDEF1    1:BDEF2    2:BDEF4  3:SDEF  4:SDEF
		unsigned char	edgeFlag;		///< �G�b�W�t���O
	};
	/*!-----------------------------------------------------------
	//	@struct	AppendixUV
	//	@brief	�ǉ�UV
	//					Header ��AppendUV���ǂݍ���
	------------------------------------------------------------*/
	struct	AppendixUV//*num���ǂݍ���
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
	/*!-----------------------------------------------------------
	//	@struct	PMXTexture
	//	@brief		�ގ����Ŏg�p�����e�N�X�`���p�X�e�[�u��
	------------------------------------------------------------*/
	struct	TexturePathTable//*num���ǂݍ���
	{
		unsigned	int	texturesize;					//�e�N�X�`���p�X�e�[�u���̑傫��
		unsigned	int  texturePathTable;		//�e�N�X�`���p�X�e�[�u��
	};
	/*!-----------------------------------------------------------
	//	@struct	PMXMaterial
	//	@brief	�ގ��f�[�^
	------------------------------------------------------------*/
	struct Material {
		float diffuseColor[4];		///< �f�B�t���[�Y�F
		float specularColor[3];		///< �X�y�L�����J���[
		float specularity;			///< �X�y�L�����W��
		float ambientColor[3];			///< �A���r�G���g
		unsigned char drawflag;		/*	[0x01] bothSide		[0x02] shadow	[0x04] self shadow map	[0x08] self shadow	[0x10] edge*/
		float	edgeColor[4];
		float	edgeSize;
		unsigned int textureindex;		//�ʏ�e�N�X�`���̃C���f�b�N�X
		unsigned int sphereindex;		//�X�t�B�A�e�N�X�`���̃C���f�b�N�X
		unsigned char spheremode;		//�X�t�B�A���[�h 0:���� 1:��Z(sph) 2:���Z(spa) 3:�T�u�e�N�X�`��(�ǉ�UV1)
		unsigned char	toonflg;			//���L�g�D�[���t���O0:�p���l�͌�Toon 1:�p���l�͋��LToon�ǂ��炩����Ȃ̂Œ���
		unsigned int	textsize;			//�e�L�X�g�T�C�Y
		unsigned char	text;			//�e�L�X�g
		unsigned int facevertexcount;		//�ގ��ɑΉ������(���_)�� (�K��3�̔{���ɂȂ�)
	};
	/*!-----------------------------------------------------------
	//	@struct	PMXIKLink
	//	@brief	�ގ��f�[�^
	------------------------------------------------------------*/
	struct IKLink {
		unsigned int idxBone = 0;
		unsigned char bLimit = 0;
		std::array<float, 3>  vMin;//bLimit=1
		std::array<float, 3>  vMax;//bLimit=1
	};
	/*!-----------------------------------------------------------
	//	@struct	PMXIKBone
	//	@brief	�ގ��f�[�^
	------------------------------------------------------------*/
	struct IKBone {
		unsigned int idxBone = 0;
		int nLoop = 0;
		float fLimitAng = 0;
		std::vector<IKLink> aLink;
	};


	/*!-----------------------------------------------------------
	//	@struct	PMXBone
	//	@brief	�ގ��f�[�^
	------------------------------------------------------------*/
	struct Bone {
		enum {
			BIT_JOINT = 0x0001,			// �ڑ���(PMD�q�{�[���w��)�\�����@ -> 0:���W�I�t�Z�b�g�Ŏw�� 1:�{�[���Ŏw��
			BIT_ROT = 0x0002,			// ��]�\
			BIT_MOVE = 0x0004,			// �ړ��\
			BIT_VISIBLE = 0x0008,		// �\��
			BIT_MANIP = 0x0010,			// �����
			BIT_IK = 0x0020,			// IK
			BIT_GIVE_LOCAL = 0x0080,	// ���[�J���t�^ | �t�^�Ώ� 0:���[�U�[�ό`�l�^IK�����N�^���d�t�^ 1:�e�̃��[�J���ό`��
			BIT_GIVE_ROT = 0x0100,		// ��]�t�^
			BIT_GIVE_MOVE = 0x0200,		// �ړ��t�^
			BIT_FIX_AXIS = 0x0400,		// ���Œ�
			BIT_LOCAL_AXIS = 0x0800,	// ���[�J����
			BIT_POST_PHYSICS = 0x1000,	// ������ό`
			BIT_EXT_PARENT = 0x2000,	// �O���e�ό`
		};

		std::string boneName;		//�{�[���̖��O
		std::string  boneEnglishName;		//�{�[���p��
		std::array<float, 3>	pos;	 //�|�W�V����
		unsigned int ParentIndex = 0;	//�e�{�[���̃C���f�b�N�X
		unsigned int tranceHyerarky = 0;		//�ό`�K�w
		unsigned short bitflg = 0;		//�r�b�g�t���O
		std::array<float, 3> Joint;		//BIT_JOINT=0
		unsigned int IndexJoint = 0;			//BIT_JOINT=1
		unsigned int GiveIndex = 0;			///BIT_GIVE_ROT=1 || BIT_GIVE_MOVE=1
		float Give = 0;			//BIT_GIVE_ROT=1 || BIT_GIVE_MOVE=1		�t�^��
		std::array<float, 3> vFixAxis;		//BIT_FIX_AXIS=1
		std::array<float, 3> vAxisX;		//BIT_LOCAL_AXIS=1
		std::array<float, 3> vAxisZ;			//BIT_LOCAL_AXIS=1
		int iExtParent = 0;//BIT_EXT_PARENT=1
		IKBone Ik;
	};



	/*!-----------------------------------------------------------
	//	@struct	PMXBone
	//	@brief	���_���[�t
	------------------------------------------------------------*/
	struct PMX_MORPH_VERTEX {
		int		Index;								// ���_�C���f�b�N�X
		float	Offset[3];							// ���_���W�I�t�Z�b�g
	};

	// �t�u���[�t���
	struct PMX_MORPH_UV {
		int		Index;								// ���_�C���f�b�N�X
		float	Offset[4];							// ���_�t�u�I�t�Z�b�g
	};

	// �{�[�����[�t���
	struct PMX_MORPH_BONE {
		int		Index;								// �{�[���C���f�b�N�X
		float	Offset[3];							// ���W�I�t�Z�b�g
		float	Quat[4];							// ��]�N�H�[�^�j�I��
	};

	// �ގ����[�t���
	struct PMX_MORPH_MATERIAL {
		int		Index;								// �}�e���A���C���f�b�N�X
		BYTE	CalcType;							// �v�Z�^�C�v( 0:��Z  1:���Z )
		float	Diffuse[4];							// �f�B�t���[�Y�J���[
		float	Specular[3];						// �X�y�L�����J���[
		float	SpecularPower;						// �X�y�L�����W��
		float	Ambient[3];							// �A���r�G���g�J���[
		float	EdgeColor[4];						// �G�b�W�J���[
		float	EdgeSize;							// �G�b�W�T�C�Y
		float	TextureScale[4];					// �e�N�X�`���W��
		float	SphereTextureScale[4];				// �X�t�B�A�e�N�X�`���W��
		float	ToonTextureScale[4];				// �g�D�[���e�N�X�`���W��
	};

	// �O���[�v���[�t
	struct PMX_MORPH_GROUP {
		int		Index;								// ���[�t�C���f�b�N�X
		float	Ratio;								// ���[�t��
	};

	// ���[�t���
	struct PMX_MORPH {
		std::string	Name;							// ���O

		BYTE	ControlPanel;						// ����p�l��
		BYTE	Type;								// ���[�t�̎��  0:�O���[�v 1:���_ 2:�{�[�� 3:UV 4:�ǉ�UV1 5:�ǉ�UV2 6:�ǉ�UV3 7:�ǉ�UV4 8:�ގ�

		int		DataNum;							// ���[�t���̐�

		union {
			PMX_MORPH_VERTEX *Vertex;				// ���_���[�t
			PMX_MORPH_UV *UV;						// UV���[�t
			PMX_MORPH_BONE *Bone;					// �{�[�����[�t
			PMX_MORPH_MATERIAL *Material;			// �}�e���A�����[�t
			PMX_MORPH_GROUP *Group;				// �O���[�v���[�t
		};
	};

	// ���̏��
	struct PMX_RIGIDBODY {
		std::string	Name;						// ���O

		unsigned int		BoneIndex = 0;							// �Ώۃ{�[���ԍ�

		BYTE	RigidBodyGroupIndex = 0;				// ���̃O���[�v�ԍ�
		WORD	RigidBodyGroupTarget = 0;				// ���̃O���[�v�Ώ�

		BYTE	ShapeType = 0;							// �`��( 0:��  1:��  2:�J�v�Z�� )
		float	Shape[3];							// ��,�����A���s��

		float	Position[3];						// �ʒu
		float	Rotation[3];						// ��]( ���W�A�� )

		float	RigidBodyWeight = 0;					// ����
		float	RigidBodyPosDim = 0;					// �ړ�����
		float	RigidBodyRotDim = 0;					// ��]����
		float	RigidBodyRecoil = 0;					// ������
		float	RigidBodyFriction = 0;					// ���C��

		BYTE	RigidBodyType = 0;						// ���̃^�C�v( 0:Bone�Ǐ]  1:�������Z  2:�������Z(Bone�ʒu���킹) )
	};

	// �W���C���g���
	struct PMX_JOINT {
		std::string	Name;						// ���O

		BYTE	Type;								// ���( 0:�X�v�����O6DOF ( PMX2.0 �ł� 0 �̂� )

		int		RigidBodyAIndex;					// �ڑ��捄�̂`
		int		RigidBodyBIndex;					// �ڑ��捄�̂a

		float	Position[3];						// �ʒu
		float	Rotation[3];						// ��]( ���W�A�� )

		float	ConstrainPositionMin[3];			// �ړ�����-����
		float	ConstrainPositionMax[3];			// �ړ�����-���
		float	ConstrainRotationMin[3];			// ��]����-����
		float	ConstrainRotationMax[3];			// ��]����-���

		float	SpringPosition[3];				// �o�l�萔-�ړ�
		float	SpringRotation[3];				// �o�l�萔-��]
	};


#pragma pack(pop)
};


class PmxLoader :public MeshLoader {

	/*!-----------------------------------------------------------
	//	@struct	VERTEX
	//	@brief	�X�L�����b�V���p�̒��_�f�[�^
	------------------------------------------------------------*/
	struct Vertex {
		union {
			struct {
				float	x, y, z;
				float	nx, ny, nz;
				float	u, v;
			};
			struct {
				float baseData[8];
			};
		};
		union {
			struct {
				float	weight[4];
				int		index[4];
				unsigned char weighttype;
			};
			struct {
				float skinData[9];
			};
		};
	};

	struct Material {
		std::array<float, 4>	diffuse;	///< Diffuse����
		std::array<float, 4>	specular;	///< ���ʔ��˂̐���(a:�X�y�L�������x�j
		std::array<float, 3>	emissive;	///< ���Ȕ����̐���
		unsigned	int	textureEntry;
		unsigned	int	indexnum;
	};

	/*!-----------------------------------------------------------
	//	@struct	BoneRelation
	//	@brief	�f�[�^���^�Ԃ��߂̃{�[���f�[�^
	------------------------------------------------------------*/
	struct BoneRelation {
		char		name[30];		///< �{�[����
		WORD		firstChildID;	///< ���q�{�[���C���f�b�N�X(�Ȃ����0xffff)
		WORD		siblingID;		///< �Z��{�[���C���f�b�N�X(�Ȃ����0xffff)
		WORD		parentID;		///< �e�{�[���C���f�b�N�X(�Ȃ����0xffff)s
		float		length;			///< �{�[���̒���
		XMFLOAT4X4		initMtx;	///< �{�[�������s��
	};

	struct IKBone {
		WORD	boneIndex;			///< IK�{�[���ԍ��i�C���f�b�N�X�j
		WORD	effectorBoneIndex;	///< IK�{�[���̈ʒu�ɁA���̃{�[������v������悤��IK�������s����
		BYTE	chainLength;		///< IK�`�F�[���̒���
		WORD	numIterations;		///< �ċA���Z��
		FLOAT	controlWeight;		///< �{�[���̒P�ʐ����p 1.0->4.0[rad]. �܂��u�Ђ��v�Ƃ������O�̃{�[����X�������ɂ��������Ȃ�����������
		std::vector<USHORT>  childBoneIndexVector;	///< �q��IK�̃C���f�b�N�Xvector
	};

public:
	PmxLoader() {};
	~PmxLoader() {

	};


	std::vector<Vertex> vertexBuffer;
	std::vector<VertexSkin> vertex;
	std::vector<DWORD> indexBuffer;
	std::vector<Material> materialBuffer;
	std::vector<PmxMaterialBase> material;
	std::vector<tstring>	texturefilepath;
	std::vector<Pmx::Bone>		Bonebuff;
	std::vector<MMDBone> bone;
	std::vector<MMDIKBone> ikBone;
	std::vector<Pmx::PMX_MORPH> morph;
	std::vector<Pmx::PMX_RIGIDBODY> rigid_body;
	std::vector<Pmx::PMX_JOINT> joint;
	unsigned int IkBonenum = 0;
	/*!-----------------------------------------------------------
	//	@brief		�ǂݍ���
	//	@param[in]	_filePath	�t�@�C���p�X
	//	@return		�����I�u�W�F�N�g�̃|�C���^
	------------------------------------------------------------*/


	virtual bool LoadFromFile(const tstring& filename) override;
	virtual bool LoadFromMemory(void *memory, size_t size) override;
	virtual int GetMeshNum()override;
	virtual int GetVertexSize(int index)override;
	virtual void *GetVertexBuffer(int index)override;
	virtual size_t GetVertexStride()override;
	virtual size_t GetIndexBufferSize(int Index)override;
	virtual void *GetIndexBuffer(int index)override;
	PmxMaterialBase *GetMaterial(int index);
	size_t GetMaterialNum();
private:

private:
	bool Load(const pmxString _filePath);
	bool CreateMotionBone(std::vector<MMDBone>* b, std::vector<MMDIKBone>* p);
	bool CreateMesh(SkinMeshObject *_mesh, DX11Device *dev);
	bool LoadPmxHeader(Pmx::Header*	pHeader, unsigned char** buffer);
	bool LoadPMXVertex(Pmx::Header*	pHeader, unsigned char** buffer);
	bool LoadPMXIndex(Pmx::Header*	pHeader, unsigned char** buffer);
	bool LoadPMXMaterial(Pmx::Header*	pHeader, unsigned char** buffer);
	bool LoadPMXTexture(Pmx::Header*	pHeader, unsigned char** buffer, const	char*	pFileName);
	void CreateUTF16Texture(Pmx::Header*	pHeader, unsigned char** buffer, const	char*	pFileName);
	void CreateUTF8Texture(Pmx::Header*	pHeader, unsigned char** buffer, const	char*	pFileName);
	bool CreateUTF16Bone(Pmx::Header*	pHeader, unsigned char** buffer);
	bool CreateUTF8Bone(Pmx::Header*	pHeader, unsigned char** buffer);
	void CopyMaterial(PmxMaterialBase &material, const  Material& Material);
	bool LoadPMXBone(Pmx::Header*	pHeader, unsigned char** buffer);
	void CreateBone(std::vector<MMDBone>* b);
	void CreateIKBone(std::vector<MMDIKBone>* p);
	bool CreateMotionBone(std::vector<MMDBone> &b, std::vector<MMDIKBone> &p);
	bool LoadPMXMorph(Pmx::Header*	pHeader, unsigned char** buffer);
	bool LoadPMXRigid(Pmx::Header*	pHeader, unsigned char** buffer);
	bool LoadPMXJoint(Pmx::Header*	pHeader, unsigned char** buffer);
	bool MovePMX(Pmx::Header*	pHeader, unsigned char** buffer);
	bool CreateUTF16Morph(Pmx::Header*	pHeader, unsigned char** buffer);
	bool CreateUTF8Morph(Pmx::Header*	pHeader, unsigned char** buffer);
	bool CreateUTF16Rigid(Pmx::Header*	pHeader, unsigned char** buffer);
	bool CreateUTF8Rigid(Pmx::Header*	pHeader, unsigned char** buffer);
	bool CreateUTF16Joint(Pmx::Header*	pHeader, unsigned char** buffer);
	bool CreateUTF8Joint(Pmx::Header*	pHeader, unsigned char** buffer);
};