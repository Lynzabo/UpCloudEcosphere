/*
SQLyog Ultimate v11.24 (32 bit)
MySQL - 5.1.73-community : Database - c##nodeserver
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`c##nodeserver` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `c##nodeserver`;

/*Table structure for table `ns_r_schedule_send_files` */

DROP TABLE IF EXISTS `ns_r_schedule_send_files`;

CREATE TABLE `ns_r_schedule_send_files` (
  `UUID` varchar(32) NOT NULL COMMENT 'UUID',
  `FILE_URL` varchar(500) NOT NULL COMMENT '文件下载地址',
  `FILE_ABST` varchar(500) NOT NULL COMMENT '文件保存路径',
  `TASK_UUID` varchar(32) NOT NULL COMMENT '任务UUID',
  `STATE` char(1) NOT NULL COMMENT '状态',
  `ERROR` varchar(500) DEFAULT NULL COMMENT '错误信息',
  PRIMARY KEY (`UUID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='控制传输任务下发文件处理表\r\n存放控制传输任务下发文件';

/*Data for the table `ns_r_schedule_send_files` */

/*Table structure for table `ns_r_schedule_task` */

DROP TABLE IF EXISTS `ns_r_schedule_task`;

CREATE TABLE `ns_r_schedule_task` (
  `UUID` varchar(32) NOT NULL COMMENT 'UUID',
  `TASK_NUM` int(11) NOT NULL COMMENT '计划任务编号',
  `STRATEGY` int(11) NOT NULL COMMENT '执行策略',
  `STATE` char(1) NOT NULL COMMENT '任务状态',
  `EXEC_TIME` varchar(50) NOT NULL COMMENT '任务执行时刻',
  `SAVE_ABST` varchar(500) NOT NULL COMMENT '入口文件保存路径',
  `INSERT_TIME` varchar(50) NOT NULL COMMENT '添加时间',
  PRIMARY KEY (`UUID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='控制传输任务处理表\r\n任务状态代表任务状态';

/*Data for the table `ns_r_schedule_task` */

/*Table structure for table `ns_r_struct_send_files` */

DROP TABLE IF EXISTS `ns_r_struct_send_files`;

CREATE TABLE `ns_r_struct_send_files` (
  `UUID` varchar(32) NOT NULL COMMENT 'UUID',
  `FILE_URL` varchar(500) NOT NULL COMMENT '文件下载地址',
  `FILE_ABST` varchar(500) NOT NULL COMMENT '文件保存路径',
  `SEQUENCE` int(11) NOT NULL COMMENT '文件解析次序',
  `TASK_UUID` varchar(32) NOT NULL COMMENT '任务UUID',
  `STATE` char(1) NOT NULL COMMENT '状态',
  `ERROR` varchar(500) DEFAULT NULL COMMENT '错误信息',
  PRIMARY KEY (`UUID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='结构化任务下发文件处理表\r\n存放结构化任务下发文件';

/*Data for the table `ns_r_struct_send_files` */

/*Table structure for table `ns_r_struct_task` */

DROP TABLE IF EXISTS `ns_r_struct_task`;

CREATE TABLE `ns_r_struct_task` (
  `UUID` varchar(32) NOT NULL COMMENT 'UUID',
  `TASK_NUM` int(11) NOT NULL COMMENT '计划任务编号',
  `STRATEGY` int(11) NOT NULL COMMENT '下发策略',
  `STATE` char(1) NOT NULL COMMENT '任务状态',
  `EXEC_TIME` varchar(50) NOT NULL COMMENT '任务执行时刻',
  `INSERT_TIME` varchar(50) NOT NULL COMMENT '添加时间',
  PRIMARY KEY (`UUID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='结构化任务处理表\r\n任务状态代表任务状态';

/*Data for the table `ns_r_struct_task` */

/*Table structure for table `ns_r_unstruct_send_files` */

DROP TABLE IF EXISTS `ns_r_unstruct_send_files`;

CREATE TABLE `ns_r_unstruct_send_files` (
  `UUID` varchar(32) NOT NULL COMMENT 'UUID',
  `FILE_URL` varchar(500) NOT NULL COMMENT '文件下载地址',
  `FILE_ABST` varchar(500) NOT NULL COMMENT '文件保存路径',
  `TASK_UUID` varchar(32) NOT NULL COMMENT '任务UUID',
  `STATE` char(1) NOT NULL COMMENT '状态',
  `ERROR` varchar(500) DEFAULT NULL COMMENT '错误信息',
  PRIMARY KEY (`UUID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='非结构化任务下发文件处理表\r\n存放非结构化任务下发文件';

/*Data for the table `ns_r_unstruct_send_files` */

/*Table structure for table `ns_r_unstruct_task` */

DROP TABLE IF EXISTS `ns_r_unstruct_task`;

CREATE TABLE `ns_r_unstruct_task` (
  `UUID` varchar(32) NOT NULL COMMENT 'UUID',
  `TASK_NUM` int(11) NOT NULL COMMENT '计划任务编号',
  `STRATEGY` int(11) NOT NULL COMMENT '下发策略',
  `STATE` char(1) NOT NULL COMMENT '任务状态',
  `INSERT_TIME` varchar(50) NOT NULL COMMENT '添加时间',
  PRIMARY KEY (`UUID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='非结构化任务处理表\r\n任务状态代表任务状态，0代表废弃状态，1代表任务可用，2代表正在下载，3代表下载出错，4代表下载成';

/*Data for the table `ns_r_unstruct_task` */

/*Table structure for table `ns_s_schedule_send_files` */

DROP TABLE IF EXISTS `ns_s_schedule_send_files`;

CREATE TABLE `ns_s_schedule_send_files` (
  `UUID` varchar(32) NOT NULL COMMENT 'UUID',
  `FILE_URL` varchar(500) NOT NULL COMMENT '文件下载地址',
  `FILE_ABST` varchar(500) NOT NULL COMMENT '文件保存路径',
  `TASK_UUID` varchar(32) NOT NULL COMMENT '任务UUID',
  `STATE` char(1) NOT NULL COMMENT '状态',
  `ERROR` varchar(500) DEFAULT NULL COMMENT '错误信息',
  PRIMARY KEY (`UUID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='控制传输任务下发文件处理归档表\r\n存放控制传输任务下发文件';

/*Data for the table `ns_s_schedule_send_files` */

/*Table structure for table `ns_s_schedule_task` */

DROP TABLE IF EXISTS `ns_s_schedule_task`;

CREATE TABLE `ns_s_schedule_task` (
  `UUID` varchar(32) NOT NULL COMMENT 'UUID',
  `TASK_NUM` int(11) NOT NULL COMMENT '计划任务编号',
  `STRATEGY` int(11) NOT NULL COMMENT '执行策略',
  `STATE` char(1) NOT NULL COMMENT '任务状态',
  `EXEC_TIME` varchar(50) NOT NULL COMMENT '任务执行时刻',
  `SAVE_ABST` varchar(500) NOT NULL COMMENT '入口文件保存路径',
  `INSERT_TIME` varchar(50) NOT NULL COMMENT '添加时间',
  PRIMARY KEY (`UUID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='控制传输任务处理归档表\r\n任务状态代表任务状态';

/*Data for the table `ns_s_schedule_task` */

/*Table structure for table `ns_s_struct_send_files` */

DROP TABLE IF EXISTS `ns_s_struct_send_files`;

CREATE TABLE `ns_s_struct_send_files` (
  `UUID` varchar(32) NOT NULL COMMENT 'UUID',
  `FILE_URL` varchar(500) NOT NULL COMMENT '文件下载地址',
  `FILE_ABST` varchar(500) NOT NULL COMMENT '文件保存路径',
  `SEQUENCE` int(11) NOT NULL COMMENT '文件解析次序',
  `TASK_UUID` varchar(32) NOT NULL COMMENT '任务UUID',
  `STATE` char(1) NOT NULL COMMENT '状态',
  `ERROR` varchar(500) DEFAULT NULL COMMENT '错误信息',
  PRIMARY KEY (`UUID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='结构化任务下发文件处理归档表\r\n存放结构化任务下发文件';

/*Data for the table `ns_s_struct_send_files` */

/*Table structure for table `ns_s_struct_task` */

DROP TABLE IF EXISTS `ns_s_struct_task`;

CREATE TABLE `ns_s_struct_task` (
  `UUID` varchar(32) NOT NULL COMMENT 'UUID',
  `TASK_NUM` int(11) NOT NULL COMMENT '计划任务编号',
  `STRATEGY` int(11) NOT NULL COMMENT '下发策略',
  `STATE` char(1) NOT NULL COMMENT '任务状态',
  `EXEC_TIME` varchar(50) NOT NULL COMMENT '任务执行时刻',
  `INSERT_TIME` varchar(50) NOT NULL COMMENT '添加时间',
  PRIMARY KEY (`UUID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='结构化任务处理归档表\r\n任务状态代表任务状态';

/*Data for the table `ns_s_struct_task` */

/*Table structure for table `ns_s_unstruct_send_files` */

DROP TABLE IF EXISTS `ns_s_unstruct_send_files`;

CREATE TABLE `ns_s_unstruct_send_files` (
  `UUID` varchar(32) NOT NULL COMMENT 'UUID',
  `FILE_URL` varchar(500) NOT NULL COMMENT '文件下载地址',
  `FILE_ABST` varchar(500) NOT NULL COMMENT '文件保存路径',
  `TASK_UUID` varchar(32) NOT NULL COMMENT '任务UUID',
  `STATE` char(1) NOT NULL COMMENT '状态',
  `ERROR` varchar(500) DEFAULT NULL COMMENT '错误信息',
  PRIMARY KEY (`UUID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='非结构化任务下发文件处理归档表\r\n存放非结构化任务下发文件';

/*Data for the table `ns_s_unstruct_send_files` */

/*Table structure for table `ns_s_unstruct_task` */

DROP TABLE IF EXISTS `ns_s_unstruct_task`;

CREATE TABLE `ns_s_unstruct_task` (
  `UUID` varchar(32) NOT NULL COMMENT 'UUID',
  `TASK_NUM` int(11) NOT NULL COMMENT '计划任务编号',
  `STRATEGY` int(11) NOT NULL COMMENT '下发策略',
  `STATE` char(1) NOT NULL COMMENT '任务状态',
  `INSERT_TIME` varchar(50) NOT NULL COMMENT '添加时间',
  PRIMARY KEY (`UUID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='非结构化任务处理归档表\r\n任务状态代表任务状态';

/*Data for the table `ns_s_unstruct_task` */

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
