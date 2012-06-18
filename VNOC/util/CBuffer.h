#pragma once
#include <wtypes.h>

// 非线程安全，请自维护访问互斥或考虑添加互斥功能
class CBuffer
{
public:
	CBuffer(LPCTSTR _debug=NULL);	// 用于记录一个标记，好追踪释放的时候的错误
	~CBuffer();
public:
	// 分配。即使原来的没释放也没事
	BYTE* Alloc(DWORD size);

	// 清空
	VOID Clear();
	
	// 获取堆内存指针。
	BYTE* GetBuffer() const;

	// 获取大小
	DWORD GetSize() const;

	// 拷贝数据
	const BYTE* Copy(const void* src,DWORD len);
	const BYTE* Copy(const CBuffer& src);

	// 托管内存空间
	VOID Attach(void* buffer,size_t bufsize);
	VOID Detach();

	// 写入文件
	BOOL WriteToFile(LPCTSTR filePath) const;

	// 赋值
	void memset(byte value=0);
	DWORD Write(void* p,DWORD size,DWORD startPos=0);

	operator const BYTE* () const;
private:
	void operator =(const CBuffer &src);
	void _free();
protected:
	BYTE* m_pBuf;
	DWORD m_bufSize;
	BOOL m_attached;
#ifdef _DEBUG
	LPCTSTR m_debug;
#endif
};

#define ConstReferenceBuffer const CBuffer&		// 常引用
#define BufferIn CBuffer	// 调用者负责分配、释放
#define BufferOut CBuffer	// 调用者负责释放、函数负责分配

// 管道型Buffer
class CStreamBuffer : public CBuffer
{
public:
	CStreamBuffer();
	~CStreamBuffer();
public:
	// 写入,返回实际写入字节数
	DWORD Append(const void *pData,DWORD dataSize);

	// 读取,返回实际读取字节数
	DWORD Get(void *pOut,DWORD bytesToRead);
	void ResetWritePos();
	void ResetReadPos();
private:
	void operator =(const CStreamBuffer &src);
	volatile DWORD m_writePos;		// 写入位置，就是个数组下标
	DWORD m_readPos;
};