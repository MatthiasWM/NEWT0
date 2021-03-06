/*------------------------------------------------------------------------*/
/**
 * @file	NewtObj.h
 * @brief   オブジェクトシステム
 *
 * @author  M.Nukui
 * @date	2003-11-07
 *
 * Copyright (C) 2003-2004 M.Nukui All rights reserved.
 */


#ifndef	NEWTOBJ_H
#define	NEWTOBJ_H

#include <assert.h>

/* ヘッダファイル */
#include "NewtType.h"


/* マクロ */
/// addr <--> integer　時のシフト
//#define NOBJ_ADDR_SHIFT		2
#define NOBJ_ADDR_SHIFT		0

#ifdef __cplusplus
extern "C" {
#endif

/* 定数 */

enum {
    kNewtNotFunction			= 0,
    kNewtCodeBlock,                     // バイトコード関数
    kNewtCodeBlock21,                   // NewtonOS 2.1 function block
    kNewtNativeFn,						// ネイティブ関数（rcvrなし、old style）
    kNewtNativeFunc						// ネイティブ関数（rcvrあり、new style）
};


/* 型宣言 */

/// 拡張ライブラリのインストール用エントリ関数
typedef void(*newt_install_t)(void);


/* 関数プロトタイプ */

uint32_t	NewtSymbolHashFunction(const char * name);
newtRef		NewtLookupSymbol(newtRefArg r, const char * name, uint32_t hash, int32_t st);
newtRef		NewtLookupSymbolArray(newtRefArg r, newtRefArg name, int32_t st);
const char*	NewtSymbolGetName(newtRefArg inSymbol);

uint16_t	NewtGetRefType(newtRefArg r, bool detail);
uint16_t	NewtGetObjectType(newtObjRef obj, bool detail);

uint32_t	NewtObjCalcDataSize(uint32_t n);
newtObjRef	NewtObjAlloc(newtRefArg r, uint32_t n, uint16_t type, bool literal);
newtObjRef	NewtObjResize(newtObjRef r, uint32_t n);
void *		NewtObjData(newtObjRef obj);
newtRef		NewtObjClone(newtRefArg r);
newtRef		NewtPackLiteral(newtRefArg r);

bool		NewtRefIsLiteral(newtRefArg r);
bool		NewtRefIsSweep(newtRefArg r, bool mark);
bool		NewtRefIsNIL(newtRefArg r);
bool		NewtRefIsSymbol(newtRefArg r);
uint32_t	NewtRefToHash(newtRefArg r);
bool		NewtRefIsString(newtRefArg r);
bool		NewtRefIsInteger(newtRefArg r);
int64_t		NewtRefToInteger(newtRefArg r);
bool		NewtRefIsInt64(newtRefArg r);
bool		NewtRefIsReal(newtRefArg r);
double		NewtRefToReal(newtRefArg r);
bool		NewtRefIsBinary(newtRefArg r);
void *		NewtRefToData(newtRefArg r);
bool		NewtRefIsArray(newtRefArg r);
bool		NewtRefIsFrame(newtRefArg r);
bool		NewtRefIsFrameOrArray(newtRefArg r);
bool		NewtRefIsImmediate(newtRefArg r);
bool		NewtRefIsCodeBlock(newtRefArg r);
bool		NewtRefIsNativeFn(newtRefArg r);
bool		NewtRefIsNativeFunc(newtRefArg r);
bool		NewtRefIsFunction(newtRefArg r);
int			NewtRefFunctionType(newtRefArg r);
bool		NewtRefIsRegex(newtRefArg r);
void *		NewtRefToAddress(newtRefArg r);

newtRef		NewtMakeBinary(newtRefArg klass, uint8_t * data, uint32_t size, bool literal);
newtRef		NewtMakeBinaryFromHex(newtRefArg klass, const char *hex, bool literal);
newtRef     NewtMakeBinaryFromBC(newtRefArg byteCodeArray, bool literal);
newtRef		NewtMakeSymbol(const char *s);
newtRef		NewtMakeString(const char *s, bool literal);
newtRef		NewtMakeString2(const char *s, uint32_t len, bool literal);
newtRef		NewtBinarySetLength(newtRefArg r, uint32_t n);
newtRef		NewtStringSetLength(newtRefArg r, uint32_t n);
newtRef		NewtMakeInteger(int64_t v);
newtRef		NewtMakeInt64(int64_t v);
newtRef		NewtMakeReal(double v);
newtRef		NewtMakeArray(newtRefArg klass, uint32_t n);
newtRef		NewtMakeArray2(newtRefArg klass, uint32_t n, const newtRefVar v[]);
newtRef		NewtMakeMap(newtRefArg superMap, uint32_t n, newtRefVar v[]);
void		NewtSetMapFlags(newtRefArg map, int32_t bit);
void		NewtClearMapFlags(newtRefArg map, int32_t bit);
uint32_t	NewtMapLength(newtRefArg map);
newtRef		NewtMakeFrame(newtRefArg map, uint32_t n);
newtRef		NewtMakeFrame2(uint32_t n, newtRefVar v[]);
newtRef		NewtMakeSlotsObj(newtRefArg r, uint32_t n, uint16_t type);
uint32_t	NewtObjSlotsLength(newtObjRef obj);
newtRef		NewtObjAddArraySlot(newtObjRef obj, newtRefArg v);
newtRef		NewtSlotsSetLength(newtRefArg r, uint32_t n, newtRefArg v);
newtRef		NewtSetLength(newtRefArg r, uint32_t n);
newtRef		NewtMakeAddress(void * addr);

newtRef		NewtThrow0(int32_t err); 
newtRef		NewtThrow(int32_t err, newtRefArg value); 
newtRef		NewtThrowSymbol(int32_t err, newtRefArg symbol); 
newtRef		NewtErrOutOfBounds(newtRefArg value, int32_t index);
void		NewtErrMessage(int32_t err);
const char * NewtErrorMessage(int32_t err);

int			NewtSymbolCompareLex(newtRefArg r1, newtRefArg r2);
int16_t		NewtObjectCompare(newtRefArg r1, newtRefArg r2);
bool		NewtRefEqual(newtRefArg r1, newtRefArg r2);
bool		NewtObjectEqual(newtRefArg r1, newtRefArg r2);
bool		NewtSymbolEqual(newtRefArg r1, newtRefArg r2);

uint32_t	NewtLength(newtRefArg r);
uint32_t	NewtDeeplyLength(newtRefArg r);
uint32_t	NewtBinaryLength(newtRefArg r);
uint32_t	NewtSymbolLength(newtRefArg r);
uint32_t	NewtStringLength(newtRefArg r);
uint32_t	NewtSlotsLength(newtRefArg r);
uint32_t	NewtDeeplyFrameLength(newtRefArg r);

newtRef		NewtObjGetSlot(newtObjRef obj, newtRefArg slot);
newtRef		NewtObjSetSlot(newtObjRef obj, newtRefArg slot, newtRefArg v);
void		NewtObjRemoveSlot(newtObjRef obj, newtRefArg slot);

newtRef		NewtGetMapIndex(newtRefArg r, uint32_t index, uint32_t * indexP);
int32_t		NewtFindArrayIndex(newtRefArg r, newtRefArg v, uint16_t st);
bool		NewtFindMapIndex(newtRefArg r, newtRefArg v, uint32_t * indexP);
newtRef		NewtFrameMap(newtRefArg r);

int32_t		NewtFindSlotIndex(newtRefArg frame, newtRefArg slot);
bool		NewtHasProto(newtRefArg frame);
bool		NewtHasSlot(newtRefArg frame, newtRefArg slot);
newtRef		NewtSlotsGetPath(newtRefArg r, newtRefArg p);
bool		NewtHasPath(newtRefArg r, newtRefArg p);
newtRef		NewtGetPath(newtRefArg r, newtRefArg p, newtRefVar * slotP);
newtRef		NewtGetBinarySlot(newtRefArg r, uint32_t p);
newtRef		NewtSetBinarySlot(newtRefArg r, uint32_t p, newtRefArg v);
newtRef		NewtGetStringSlot(newtRefArg r, uint32_t p);
newtRef		NewtSetStringSlot(newtRefArg r, uint32_t p, newtRefArg v);
newtRef		NewtSlotsGetSlot(newtRefArg r, uint32_t p);
newtRef		NewtSlotsSetSlot(newtRefArg r, uint32_t p, newtRefArg v);
newtRef		NewtSlotsInsertSlot(newtRefArg r, uint32_t p, newtRefArg v);
newtRef		NewtGetArraySlot(newtRefArg r, uint32_t p);
newtRef		NewtSetArraySlot(newtRefArg r, uint32_t p, newtRefArg v);
newtRef		NewtInsertArraySlot(newtRefArg r, uint32_t p, newtRefArg v);
newtRef		NewtGetFrameSlot(newtRefArg r, uint32_t p);
newtRef		NewtSetFrameSlot(newtRefArg r, uint32_t p, newtRefArg v);
newtRef		NewtGetFrameKey(newtRefArg inFrame, uint32_t inIndex);

newtRef		NewtARef(newtRefArg r, uint32_t p);
newtRef		NewtSetARef(newtRefArg r, uint32_t p, newtRefArg v);

bool		NewtAssignment(newtRefArg start, newtRefArg name, newtRefArg value);
bool		NewtLexicalAssignment(newtRefArg start, newtRefArg name, newtRefArg value);
bool		NewtHasLexical(newtRefArg start, newtRefArg name);
bool		NewtHasVariable(newtRefArg r, newtRefArg name);

void *		NewtRefToNativeFn(newtRefArg r);
// old style
newtRef		NewtMakeNativeFn0(void * funcPtr, uint32_t numArgs, bool indefinite, char * doc);
newtRef		NewtDefGlobalFn0(newtRefArg sym, void * funcPtr, uint32_t numArgs, bool indefinite, char * doc);
// new style
newtRef		NewtMakeNativeFunc0(void * funcPtr, uint32_t numArgs, bool indefinite, char * doc);
newtRef		NewtDefGlobalFunc0(newtRefArg sym, void * funcPtr, uint32_t numArgs, bool indefinite, char * doc);

bool		NewtHasSubclass(newtRefArg sub, newtRefArg supr);
bool		NewtIsSubclass(newtRefArg sub, newtRefArg supr);
bool		NewtIsInstance(newtRefArg obj, newtRefArg r);

newtRef		NewtStrCat(newtRefArg r, char * s);
newtRef		NewtStrCat2(newtRefArg r, char * s, size_t slen);

newtRef		NewtGetEnv(const char * s);


static inline bool
NewtRefIsInt62(newtRefArg r)        { return ((r & 3) == 0); } ///< 30bit整数オブジェクトか？
static inline int64_t
NewtRefToInt62(newtRefArg r)        { return ((int64_t)r) >> 2; }///< オブジェクトを 30bit整数に変換
static inline newtRef
NewtMakeInt62(int64_t v)            { return (newtRef)(v << 2); } ///< 30bit整数オブジェクトを作成

static inline bool
NewtRefIsPointer(newtRefArg r)      { return ((r & 3) == 1); } ///< ポインタオブジェクトか？
static inline void*
NewtRefToPointer(newtRefArg r)      { return (void*)(r - 1); } ///< オブジェクト参照をポインタに変換
static inline newtRef
NewtMakePointer(void* v)            { return (newtRef)((uintptr_t)v + 1); } ///< ポインタオブジェクトを作成

static inline bool
NewtRefIsCharacter(newtRefArg r)    { return ((r & 0xF) == 6); } ///< 文字オブジェクトか？
static inline newtUniChar
NewtRefToCharacter(newtRefArg r)    { return (newtUniChar)((r >> 4) & 0xFFFFFFFF); } ///< オブジェクト参照を文字に変換
static inline newtRef
NewtMakeCharacter(newtUniChar v)    { return (newtRef)((((uint64_t)(v)) << 4) | 6); } ///< 文字オブジェクトを作成

static inline bool
NewtRefIsSpecial(newtRefArg r)      { return ((r & 0xF) == 2); } ///< Is it a special object?
static inline uint64_t
NewtRefToSpecial(newtRefArg r)      { return (r >> 4); } ///< Convert object reference to special value
static inline newtRef
NewtMakeSpecial(uint64_t v)         { return (newtRef)((v << 4) | 2); } ///< Create a special value


static inline bool
NewtRefIsMagicPointer(newtRefArg r)     { return ((r & 3) == 3); } ///< マジックポインタか？（数値および名前付）

#ifdef __NAMED_MAGIC_POINTER__
// TODO: verify that this is actually working. We seem to be losing the last bit of a symbol pointer here.
static inline bool
NewtRefIsNamedMP(newtRefArg r)      { return ((r & 0x8000000000000003) == 0x8000000000000003); } ///< 名前付マジックポインタか？
static inline newtRef
NewtMPToSymbol(newtRefArg r)        { return (((r << 1) & 0xFFFFFFFFFFFFFFF8) | 1); } ///< 名前付マジックポインタをシンボルに変換
static inline newtRef
NewtSymbolToMP(newtRefArg r)        { return ((r >> 1) | 0x8000000000000003); } ///< シンボルを名前付マジックポインタに変換
static inline newtRef
NewtMakeNamedMP(const char *r)      { return NewtSymbolToMP(NewtMakeSymbol(r)); } ///< 名前付マジックポインタを作成
#endif /* __NAMED_MAGIC_POINTER__ */

static inline bool
NewtRefIsNumberedMP(newtRefArg r)   { return ((r & 0x8000000000000003) == 3); } ///< 数値マジックポインタか？
static inline newtRef
NewtMakeMagicPointer(uint32_t t, uint32_t i) { return (newtRef)((t << 14) | ((i & 0x03ff) << 2) | 3); } ///< マジックポインタを作成
static inline uint32_t
NewtMPToTable(newtRefArg r)         { return (uint32_t)(r >> 14);} ///< マジックポインタのテーブル番号を取得
static inline uint32_t
NewtMPToIndex(newtRefArg r)         { return (uint32_t)((r >> 2) & 0x03ff); } ///< マジックポインタのインデックスを取得

static inline bool
NewtRefIsNotNIL(newtRefArg v)       { return (!NewtRefIsNIL(v)); } ///< NIL 以外か？
static inline newtRef
NewtMakeBoolean(bool v)             { return v ? kNewtRefTRUE : kNewtRefNIL; } ///< ブール値オブジェクトを作成

static inline uint8_t*
NewtRefToBinary(newtRefArg r)       { return (uint8_t *)NewtRefToData(r); } ///< バイナリデータへのポインタを取得
static inline newtSymDataRef
NewtRefToSymbol(newtRefArg r)       { return (newtSymDataRef)NewtRefToData(r); } ///< シンボルデータへのポインタを取得
static inline char*
NewtRefToString(newtRefArg r)       { return (char *)NewtRefToData(r); } ///< 文字列データへのポインタを取得
static inline newtRef*
NewtRefToSlots(newtRefArg r)        { return (newtRef *)NewtRefToData(r); } ///< スロットデータへのポインタを取得

//
static inline uint32_t
NewtArrayLength(newtRefArg r)       { return NewtSlotsLength(r); } ///< 配列の長さを取得
static inline uint32_t
NewtFrameLength(newtRefArg r)       { return NewtSlotsLength(r); } ///< フレームの長さを取得

//
static inline uint8_t
NewtObjType(newtObjRef v)           { return (v->header.flags & 3); } ///< オブジェクトタイプを取得
static inline bool
NewtObjIsSlotted(newtObjRef v)      { return (v->header.flags & kNewtObjSlotted) != 0; } ///< オブジェクトデータがスロットか？
static inline bool
NewtObjIsArray(newtObjRef v)        { return NewtObjType(v) == 1; } ///< オブジェクトデータが配列か？
static inline bool
NewtObjIsFrame(newtObjRef v)        { return NewtObjType(v) == 3; } ///< オブジェクトデータがフレームか？
static inline bool
NewtObjIsLiteral(newtObjRef v)      { return ((v->header.flags & kNewtObjLiteral) == kNewtObjLiteral); } ///< リテラルか？
static inline bool
NewtObjIsSweep(newtObjRef v, bool mark) { return (((v->header.flags & kNewtObjSweep) == kNewtObjSweep) == mark); } ///< スウィープ対象か？
static inline uint32_t
NewtObjSize(newtObjRef v)           { return v->header.size; } ///< オブジェクトデータのサイズを取得
static inline newtRef
NewtObjBinaryClass(newtObjRef v)    { return v->as.klass; } ///< Low-level API. Use NewtObjClassOf when needed.
static inline newtRef
NewtObjArrayClass(newtObjRef v)     { return v->as.klass; } ///< Low-level API. Use NewtObjClassOf when needed.
static inline uint8_t*
NewtObjToBinary(newtObjRef v)       { return (uint8_t *)NewtObjData(v); } ///< バイナリデータ部へのポインタ
static inline newtSymDataRef
NewtObjToSymbol(newtObjRef v)       { return (newtSymDataRef)NewtObjData(v); } ///< シンボルデータ部へのポインタ
static inline char*
NewtObjToString(newtObjRef v)       { return (char *)NewtObjData(v); } ///< 文字列データ部へのポインタ
static inline newtRef*
NewtObjToSlots(newtObjRef v)        { return (newtRef *)NewtObjData(v); } ///< スロットデータ部へのポインタ

//
extern bool NVMHasVar(newtRefArg name);

static inline bool
NewtHasVar(newtRefArg name)         { return NVMHasVar(name); } ///< 変数の存在チェック
static inline bool
NewtObjIsReadonly(newtObjRef obj)   { return NewtObjIsLiteral(obj); } ///< オブジェクトデータがリードオンリーか？
static inline bool
NewtRefIsReadonly(newtRefArg r)     { return NewtRefIsLiteral(r); } ///< オブジェクトがリードオンリーか？

#ifdef __USE_OBSOLETE_STYLE__
// old style
#define NewtMakeNativeFn(funcPtr, numArgs, doc)            NewtMakeNativeFn0(funcPtr, numArgs, false, doc)
#define NewtDefGlobalFn(sym, funcPtr, numArgs, doc)        NewtDefGlobalFn0(sym, funcPtr, numArgs, false, doc)

#endif /* __USE_OBSOLETE_STYLE__ */

// new style
static inline newtRef
NewtMakeNativeFunc(void *funcPtr, uint32_t numArgs, char *doc) { return  NewtMakeNativeFunc0(funcPtr, numArgs, false, doc); }
static inline newtRef
NewtDefGlobalFunc(newtRefArg sym, void *funcPtr, uint32_t numArgs, char *doc) { return NewtDefGlobalFunc0(sym, funcPtr, numArgs, false, doc); }


#ifdef __cplusplus
}
#endif


#endif /* NEWTOBJ_H */

