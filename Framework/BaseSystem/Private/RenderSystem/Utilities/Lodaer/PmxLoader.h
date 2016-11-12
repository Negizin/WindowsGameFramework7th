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
// 定数定義
//------------------------------------------------------------
const float PMX_MESH_SCALE = 1.0f;

class Pmx {
public:
#pragma pack(push,1)	//アラインメント制御をオフ

	/*!-----------------------------------------------------------
	//	@struct	PMXHeader
	------------------------------------------------------------*/
	struct Header {
		unsigned char	magic[4];
		float			version;
		//			ここまでマジックナンバー
		unsigned char	variousDatasizeLength;		//各種データサイズの格納数　PMXの2.0は８固定

		unsigned	char	encodeType;//0:UTF16 1:UTF8
		unsigned	char	appendUV;//追加UV
		unsigned	char	vertexIndexSize;//頂点インデックスのデータサイズ
		unsigned	char	textureIndexSize;//テクスチャインデックスのデータサイズ
		unsigned	char	materialIndexSize;//マテリアルインデックスのデータサイズ
		unsigned	char	boneIndexSize;//ボーンインデックスのデータサイズ
		unsigned	char	morphIndexSize;//モーフいんでっくすのデータサイズ
		unsigned	char	rigidIndexSize;//リジットボディインデックスのデータサイズ

		//モデル情報
		unsigned	int	nameByteSize;				//モデル名サイズ
		pmxChar*	p_PmxName;						//モデル名
		unsigned	int	nameEnglishByteSize;		//モデル英名サイズ
		pmxChar*	p_PmxNameEnglish;				//モデル英名
		unsigned	int	commentByteSize;				//コメントサイズ
		pmxChar*	p_Comment;								//コメント
		unsigned	int	commentEnglishByteSize;		//英語コメントサイズ
		pmxChar*	p_CommentEnglish;						//英語コメント
	};

	/*!-----------------------------------------------------------
	//	@struct	PMXVertex
	//	@brief	頂点データ
	------------------------------------------------------------*/
	struct Vertex {
		enum {
			BDEF1,
			BDEF2,
			BDEF4,
			SDEF,
			QDEF,
		};
		float			pos[3];			///< 頂点座標
		float			vNormal[3];		///< 法線ベクトル
		float			uv[2];			///< テクスチャ座標
		//ウェイト変形方式
		unsigned char weighttype;		//0: BDEF1    1:BDEF2    2:BDEF4  3:SDEF  4:SDEF
		unsigned char	edgeFlag;		///< エッジフラグ
	};
	/*!-----------------------------------------------------------
	//	@struct	AppendixUV
	//	@brief	追加UV
	//					Header のAppendUV分読み込む
	------------------------------------------------------------*/
	struct	AppendixUV//*num分読み込む
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
	/*!-----------------------------------------------------------
	//	@struct	PMXTexture
	//	@brief		材質内で使用されるテクスチャパステーブル
	------------------------------------------------------------*/
	struct	TexturePathTable//*num分読み込む
	{
		unsigned	int	texturesize;					//テクスチャパステーブルの大きさ
		unsigned	int  texturePathTable;		//テクスチャパステーブル
	};
	/*!-----------------------------------------------------------
	//	@struct	PMXMaterial
	//	@brief	材質データ
	------------------------------------------------------------*/
	struct Material {
		float diffuseColor[4];		///< ディフューズ色
		float specularColor[3];		///< スペキュラカラー
		float specularity;			///< スペキュラ係数
		float ambientColor[3];			///< アンビエント
		unsigned char drawflag;		/*	[0x01] bothSide		[0x02] shadow	[0x04] self shadow map	[0x08] self shadow	[0x10] edge*/
		float	edgeColor[4];
		float	edgeSize;
		unsigned int textureindex;		//通常テクスチャのインデックス
		unsigned int sphereindex;		//スフィアテクスチャのインデックス
		unsigned char spheremode;		//スフィアモード 0:無効 1:乗算(sph) 2:加算(spa) 3:サブテクスチャ(追加UV1)
		unsigned char	toonflg;			//共有トゥーンフラグ0:継続値は個別Toon 1:継続値は共有Toonどちらか一方なので注意
		unsigned int	textsize;			//テキストサイズ
		unsigned char	text;			//テキスト
		unsigned int facevertexcount;		//材質に対応する面(頂点)数 (必ず3の倍数になる)
	};
	/*!-----------------------------------------------------------
	//	@struct	PMXIKLink
	//	@brief	材質データ
	------------------------------------------------------------*/
	struct IKLink {
		unsigned int idxBone = 0;
		unsigned char bLimit = 0;
		std::array<float, 3>  vMin;//bLimit=1
		std::array<float, 3>  vMax;//bLimit=1
	};
	/*!-----------------------------------------------------------
	//	@struct	PMXIKBone
	//	@brief	材質データ
	------------------------------------------------------------*/
	struct IKBone {
		unsigned int idxBone = 0;
		int nLoop = 0;
		float fLimitAng = 0;
		std::vector<IKLink> aLink;
	};


	/*!-----------------------------------------------------------
	//	@struct	PMXBone
	//	@brief	材質データ
	------------------------------------------------------------*/
	struct Bone {
		enum {
			BIT_JOINT = 0x0001,			// 接続先(PMD子ボーン指定)表示方法 -> 0:座標オフセットで指定 1:ボーンで指定
			BIT_ROT = 0x0002,			// 回転可能
			BIT_MOVE = 0x0004,			// 移動可能
			BIT_VISIBLE = 0x0008,		// 表示
			BIT_MANIP = 0x0010,			// 操作可
			BIT_IK = 0x0020,			// IK
			BIT_GIVE_LOCAL = 0x0080,	// ローカル付与 | 付与対象 0:ユーザー変形値／IKリンク／多重付与 1:親のローカル変形量
			BIT_GIVE_ROT = 0x0100,		// 回転付与
			BIT_GIVE_MOVE = 0x0200,		// 移動付与
			BIT_FIX_AXIS = 0x0400,		// 軸固定
			BIT_LOCAL_AXIS = 0x0800,	// ローカル軸
			BIT_POST_PHYSICS = 0x1000,	// 物理後変形
			BIT_EXT_PARENT = 0x2000,	// 外部親変形
		};

		std::string boneName;		//ボーンの名前
		std::string  boneEnglishName;		//ボーン英名
		std::array<float, 3>	pos;	 //ポジション
		unsigned int ParentIndex = 0;	//親ボーンのインデックス
		unsigned int tranceHyerarky = 0;		//変形階層
		unsigned short bitflg = 0;		//ビットフラグ
		std::array<float, 3> Joint;		//BIT_JOINT=0
		unsigned int IndexJoint = 0;			//BIT_JOINT=1
		unsigned int GiveIndex = 0;			///BIT_GIVE_ROT=1 || BIT_GIVE_MOVE=1
		float Give = 0;			//BIT_GIVE_ROT=1 || BIT_GIVE_MOVE=1		付与率
		std::array<float, 3> vFixAxis;		//BIT_FIX_AXIS=1
		std::array<float, 3> vAxisX;		//BIT_LOCAL_AXIS=1
		std::array<float, 3> vAxisZ;			//BIT_LOCAL_AXIS=1
		int iExtParent = 0;//BIT_EXT_PARENT=1
		IKBone Ik;
	};



	/*!-----------------------------------------------------------
	//	@struct	PMXBone
	//	@brief	頂点モーフ
	------------------------------------------------------------*/
	struct PMX_MORPH_VERTEX {
		int		Index;								// 頂点インデックス
		float	Offset[3];							// 頂点座標オフセット
	};

	// ＵＶモーフ情報
	struct PMX_MORPH_UV {
		int		Index;								// 頂点インデックス
		float	Offset[4];							// 頂点ＵＶオフセット
	};

	// ボーンモーフ情報
	struct PMX_MORPH_BONE {
		int		Index;								// ボーンインデックス
		float	Offset[3];							// 座標オフセット
		float	Quat[4];							// 回転クォータニオン
	};

	// 材質モーフ情報
	struct PMX_MORPH_MATERIAL {
		int		Index;								// マテリアルインデックス
		BYTE	CalcType;							// 計算タイプ( 0:乗算  1:加算 )
		float	Diffuse[4];							// ディフューズカラー
		float	Specular[3];						// スペキュラカラー
		float	SpecularPower;						// スペキュラ係数
		float	Ambient[3];							// アンビエントカラー
		float	EdgeColor[4];						// エッジカラー
		float	EdgeSize;							// エッジサイズ
		float	TextureScale[4];					// テクスチャ係数
		float	SphereTextureScale[4];				// スフィアテクスチャ係数
		float	ToonTextureScale[4];				// トゥーンテクスチャ係数
	};

	// グループモーフ
	struct PMX_MORPH_GROUP {
		int		Index;								// モーフインデックス
		float	Ratio;								// モーフ率
	};

	// モーフ情報
	struct PMX_MORPH {
		std::string	Name;							// 名前

		BYTE	ControlPanel;						// 操作パネル
		BYTE	Type;								// モーフの種類  0:グループ 1:頂点 2:ボーン 3:UV 4:追加UV1 5:追加UV2 6:追加UV3 7:追加UV4 8:材質

		int		DataNum;							// モーフ情報の数

		union {
			PMX_MORPH_VERTEX *Vertex;				// 頂点モーフ
			PMX_MORPH_UV *UV;						// UVモーフ
			PMX_MORPH_BONE *Bone;					// ボーンモーフ
			PMX_MORPH_MATERIAL *Material;			// マテリアルモーフ
			PMX_MORPH_GROUP *Group;				// グループモーフ
		};
	};

	// 剛体情報
	struct PMX_RIGIDBODY {
		std::string	Name;						// 名前

		unsigned int		BoneIndex = 0;							// 対象ボーン番号

		BYTE	RigidBodyGroupIndex = 0;				// 剛体グループ番号
		WORD	RigidBodyGroupTarget = 0;				// 剛体グループ対象

		BYTE	ShapeType = 0;							// 形状( 0:球  1:箱  2:カプセル )
		float	Shape[3];							// 幅,高さ、奥行き

		float	Position[3];						// 位置
		float	Rotation[3];						// 回転( ラジアン )

		float	RigidBodyWeight = 0;					// 質量
		float	RigidBodyPosDim = 0;					// 移動減衰
		float	RigidBodyRotDim = 0;					// 回転減衰
		float	RigidBodyRecoil = 0;					// 反発力
		float	RigidBodyFriction = 0;					// 摩擦力

		BYTE	RigidBodyType = 0;						// 剛体タイプ( 0:Bone追従  1:物理演算  2:物理演算(Bone位置合わせ) )
	};

	// ジョイント情報
	struct PMX_JOINT {
		std::string	Name;						// 名前

		BYTE	Type;								// 種類( 0:スプリング6DOF ( PMX2.0 では 0 のみ )

		int		RigidBodyAIndex;					// 接続先剛体Ａ
		int		RigidBodyBIndex;					// 接続先剛体Ｂ

		float	Position[3];						// 位置
		float	Rotation[3];						// 回転( ラジアン )

		float	ConstrainPositionMin[3];			// 移動制限-下限
		float	ConstrainPositionMax[3];			// 移動制限-上限
		float	ConstrainRotationMin[3];			// 回転制限-下限
		float	ConstrainRotationMax[3];			// 回転制限-上限

		float	SpringPosition[3];				// バネ定数-移動
		float	SpringRotation[3];				// バネ定数-回転
	};


#pragma pack(pop)
};


class PmxLoader :public MeshLoader {

	/*!-----------------------------------------------------------
	//	@struct	VERTEX
	//	@brief	スキンメッシュ用の頂点データ
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
		std::array<float, 4>	diffuse;	///< Diffuse成分
		std::array<float, 4>	specular;	///< 鏡面反射の成分(a:スペキュラ強度）
		std::array<float, 3>	emissive;	///< 自己発光の成分
		unsigned	int	textureEntry;
		unsigned	int	indexnum;
	};

	/*!-----------------------------------------------------------
	//	@struct	BoneRelation
	//	@brief	データを運ぶためのボーンデータ
	------------------------------------------------------------*/
	struct BoneRelation {
		char		name[30];		///< ボーン名
		WORD		firstChildID;	///< 第一子ボーンインデックス(なければ0xffff)
		WORD		siblingID;		///< 兄弟ボーンインデックス(なければ0xffff)
		WORD		parentID;		///< 親ボーンインデックス(なければ0xffff)s
		float		length;			///< ボーンの長さ
		XMFLOAT4X4		initMtx;	///< ボーン初期行列
	};

	struct IKBone {
		WORD	boneIndex;			///< IKボーン番号（インデックス）
		WORD	effectorBoneIndex;	///< IKボーンの位置に、このボーンを一致させるようにIK処理が行われる
		BYTE	chainLength;		///< IKチェーンの長さ
		WORD	numIterations;		///< 再帰演算回数
		FLOAT	controlWeight;		///< ボーンの単位制限角 1.0->4.0[rad]. また「ひざ」という名前のボーンはX軸方向にしか動かない制限がある
		std::vector<USHORT>  childBoneIndexVector;	///< 子供IKのインデックスvector
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
	//	@brief		読み込み
	//	@param[in]	_filePath	ファイルパス
	//	@return		生成オブジェクトのポインタ
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