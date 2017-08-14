#ifndef _UJC_H_
#define _UJC_H_


#define UJC_MAGIC	0x4AEC

typedef struct{

	uint16_t magic;		//UJC_MAGIC
	uint16_t clsName;		//constant index
	uint16_t suprClsName;	//constant index
	uint16_t flags;		//java flags

	uint32_t interfaces;	//pointer into data store
	uint32_t methods;		//pointer into data store
	uint32_t fields;		//pointer into data store

	uint8_t clsNameHash;	//hash of class name

	uint8_t data[];		//data store
	
}UjcClass;

//data store layout order:	CONSTANT_REFS, CONSTANTS, INTERFACES, METHODS, FIELDS, CODE

typedef struct {
	
	uint16_t flags;		//0x00
	uint8_t nameHash;		//0x02: hash of name for quicker matching
	uint8_t typeHash;		//0x03: hash of type for quicker matching
	
	uint32_t nameAddr;	//0x04: pointer to string in constant area
	uint32_t typeAddr;	//0x07: pointer to string in constant area
	
	uint32_t codeAddr;	//0x0A: pointer to code in constant area
	
}UjcMethod;

typedef struct {

	uint16_t flags;
	uint8_t nameHash;		//hash of name for quicker matching
	uint8_t typeHash;		//hash of type for quicker matching
	uint32_t nameAddr;	//pointer to string in constant area
	uint32_t typeAddr;	//pointer to string in constant area

}UjcField;

typedef struct{

	uint16_t numConstants;	//off by one just like java
	uint32_t constantAddrs;	//pointers to data in ocnstant area
	
}UjcConstantRefs;

typedef struct{

	uint16_t numInterfaces;
	uint32_t interfaces[];	//pointers to strings in constant area

}UjcInterfaces;

typedef struct{

	uint16_t numMethods;
	UjcMethod methods[];

}UjcMethods;

typedef struct{
	
	uint16_t numFields;
	UjcField fields[];

}UjcFields;

typedef struct{
	
	uint8_t type;
	uint8_t data[];

}UjcConstant;

/* method storage in data area:

	excStruct excs [numExcs]
	uint16_t numExcs;
	uint16_t locals;
	uint16_t stackSz;
	uint8_t code[]		<----- code pointer points here


*/




#endif
