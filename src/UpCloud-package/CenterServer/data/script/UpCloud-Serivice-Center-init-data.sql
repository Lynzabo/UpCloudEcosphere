--------------------------------------------------------
--  文件已创建 - 星期一-九月-14-2015   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Table CS_CLIENT_EXTEND_INFO
--------------------------------------------------------

  CREATE TABLE "C##CENTERSERVER"."CS_CLIENT_EXTEND_INFO" 
   (	"UUID" VARCHAR2(32 BYTE), 
	"CLIENT_UUID" VARCHAR2(32 BYTE), 
	"DESCRIPTION" VARCHAR2(300 BYTE), 
	"TYPE" CHAR(1 BYTE), 
	"GROUP_UUID" VARCHAR2(32 BYTE)
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;
