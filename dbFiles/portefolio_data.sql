-- MySQL dump 10.13  Distrib 8.0.35, for Linux (x86_64)
--
-- Host: localhost    Database: portefolio
-- ------------------------------------------------------
-- Server version	8.0.35-0ubuntu0.22.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Portefolio`
--

DROP TABLE IF EXISTS `Portefolio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Portefolio` (
  `Name` varchar(255) DEFAULT NULL,
  `Value` double DEFAULT NULL,
  `Platform` varchar(255) DEFAULT NULL,
  `Type` varchar(255) DEFAULT NULL,
  `Invested_Value` double DEFAULT NULL,
  `Profits` double DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Portefolio`
--

LOCK TABLES `Portefolio` WRITE;
/*!40000 ALTER TABLE `Portefolio` DISABLE KEYS */;
/*!40000 ALTER TABLE `Portefolio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portefolioItemsList`
--

DROP TABLE IF EXISTS `portefolioItemsList`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `portefolioItemsList` (
  `Name` varchar(255) NOT NULL,
  `Value` double DEFAULT NULL,
  `Type` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portefolioItemsList`
--

LOCK TABLES `portefolioItemsList` WRITE;
/*!40000 ALTER TABLE `portefolioItemsList` DISABLE KEYS */;
INSERT INTO `portefolioItemsList` VALUES ('AMZN',138.375,'Stock'),('bitcoin',35040.058479,'Crypto'),('NVDA',450.74,'Stock'),('polkadot',4.891318,'Crypto');
/*!40000 ALTER TABLE `portefolioItemsList` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portefolio_detailed`
--

DROP TABLE IF EXISTS `portefolio_detailed`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `portefolio_detailed` (
  `id` int NOT NULL AUTO_INCREMENT,
  `Date` date DEFAULT NULL,
  `Platform` varchar(255) DEFAULT NULL,
  `Type` varchar(255) DEFAULT NULL,
  `Name` varchar(50) DEFAULT NULL,
  `Initial_Price` decimal(10,2) DEFAULT NULL,
  `Invested_Value` decimal(10,2) DEFAULT NULL,
  `Acronym` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portefolio_detailed`
--

LOCK TABLES `portefolio_detailed` WRITE;
/*!40000 ALTER TABLE `portefolio_detailed` DISABLE KEYS */;
INSERT INTO `portefolio_detailed` VALUES (1,NULL,'Etoro','Crypto','bitcoin',20000.00,40.00,'BTC'),(2,NULL,'Revolut','Crypto','polkadot',7.00,10.00,'DOT'),(3,NULL,'askdj','klj','khlh',2314.00,123.00,'kjh'),(6,NULL,'asdas','gfh','jhf',5758.00,87.00,'jhf'),(7,NULL,'ads','asd','sa',213.00,123.00,'sad'),(8,NULL,'eTORO','ASD','DSA',123.00,123.00,'DSF'),(9,NULL,'eTORO','sdad','DSA',123.00,123.00,'DSF'),(10,NULL,'eTORO','sdad','SDASD',123.00,123.00,'DSF'),(11,NULL,'Etoro','Stock','AMZN',5.00,10.00,'AMZN'),(12,NULL,'Etoro','Stock','NVDA',876.00,876.00,'NVDA'),(13,'2007-04-09','CTT','CA','CA-B',140.00,140.00,'B'),(14,'2023-09-06','reqw','dsfk','qrew',213.00,32.00,'qr'),(15,NULL,'dfsa','Stock','afds',3.00,123.00,'dfsa'),(17,NULL,'dsfdfs','dsfdf','sdfsdf',2123.00,123.00,'sdfsdf'),(18,NULL,'ads','ads','as',231.00,213.00,'ads'),(19,'2023-09-15','ads','ads','as',231.00,213.00,'ads'),(20,'1998-04-13','CTT','CA','CA-B',20.00,20.00,'B'),(23,'2017-12-29',NULL,'CA',NULL,NULL,700.00,'E'),(28,NULL,'Etoro','Crypto','bitcoin',20000.00,40.00,'BTC'),(29,'2023-11-03',NULL,'CA',NULL,NULL,200.00,'F'),(30,NULL,'Etoro','Stock','AMZN',7.00,100.00,'AMZN');
/*!40000 ALTER TABLE `portefolio_detailed` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `updatePortefolioItemList` AFTER INSERT ON `portefolio_detailed` FOR EACH ROW BEGIN
    IF NEW.Type = 'Stock' THEN
        INSERT INTO portefolioItemsList (Name, Value, Type)
        VALUES (NEW.Acronym, 0, NEW.Type)
        ON DUPLICATE KEY UPDATE Value = VALUES(Value);
    ELSEIF NEW.Type = 'Crypto' THEN
        INSERT INTO portefolioItemsList (Name, Value, Type)
        VALUES (NEW.Name, 0, NEW.Type)
        ON DUPLICATE KEY UPDATE Value = VALUES(Value);
    END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-12-29 16:41:13
