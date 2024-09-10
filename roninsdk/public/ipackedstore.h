#ifndef IPACKEDSTORE_H
#define IPACKEDSTORE_T

struct VPKData_t
{
	int             m_nHandle;
	char            pad[1];
	char            m_szPath[255];
	uint8_t         unknown2[0x134];
	int32_t         m_nEntries;
	uint8_t         unknown3[12];
//	VPKFileEntry_t* m_pEntries;
};

#endif // !IPACKEDSTORE_H