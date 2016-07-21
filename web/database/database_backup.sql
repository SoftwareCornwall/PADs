-- phpMyAdmin SQL Dump
-- version 4.5.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Jul 21, 2016 at 05:04 PM
-- Server version: 10.1.13-MariaDB
-- PHP Version: 5.6.23

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `pads_db`
--

DELIMITER $$
--
-- Procedures
--
CREATE DEFINER=`root`@`localhost` PROCEDURE `GetAllCabinetRecords` ()  BEGIN
SELECT * FROM tbl_cabinets;
END$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `GetCabinetRecord` (IN `cabID` VARCHAR(200))  BEGIN
SELECT * FROM tbl_cabinets WHERE id = cabID;
END$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `UpdateCabinetDetails` (IN `cabID` VARCHAR(200), IN `NewLocation` VARCHAR(30), IN `NewPostcode` VARCHAR(30))  NO SQL
BEGIN 
UPDATE tbl_cabinets 
SET tbl_cabinets.location = NewLocation, 
tbl_cabinets.postcode = NewPostcode 
WHERE tbl_cabinets.id = cabID; 
END$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `tbl_cabinets`
--

CREATE TABLE `tbl_cabinets` (
  `id` varchar(200) NOT NULL,
  `location` varchar(200) NOT NULL,
  `postcode` varchar(200) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `tbl_cabinets`
--

INSERT INTO `tbl_cabinets` (`id`, `location`, `postcode`) VALUES
('AA123', 'Redruth', 'TR15 73D'),
('AB123', 'Bude', 'TC83 KD3'),
('BB123', 'Bluefruit Office', 'AB12 1CD'),
('BC123', 'Car Park', 'EX00 0AA');

-- --------------------------------------------------------

--
-- Table structure for table `tbl_fleet`
--

CREATE TABLE `tbl_fleet` (
  `id` int(11) NOT NULL,
  `first_name` varchar(200) NOT NULL,
  `last_name` varchar(200) NOT NULL,
  `phone_number` varchar(200) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `tbl_guardians`
--

CREATE TABLE `tbl_guardians` (
  `id` int(11) NOT NULL,
  `cabinet_id` varchar(200) NOT NULL,
  `first_name` varchar(200) NOT NULL,
  `last_name` varchar(200) NOT NULL,
  `phone_number` varchar(200) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `tbl_guardians`
--

INSERT INTO `tbl_guardians` (`id`, `cabinet_id`, `first_name`, `last_name`, `phone_number`) VALUES
(1, 'AA123', 'Jon', 'Cole', '+447477681144'),
(2, 'AA123', 'Tyler', 'Arnold', '+447597997201');

-- --------------------------------------------------------

--
-- Table structure for table `tbl_status`
--

CREATE TABLE `tbl_status` (
  `id` int(11) NOT NULL,
  `cabinet_id` varchar(200) NOT NULL,
  `door_status` varchar(200) NOT NULL,
  `defib_status` varchar(200) NOT NULL,
  `hanger_status` varchar(200) NOT NULL,
  `alarm_status` varchar(200) NOT NULL,
  `temp_status` int(3) NOT NULL,
  `last_update` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `tbl_status`
--

INSERT INTO `tbl_status` (`id`, `cabinet_id`, `door_status`, `defib_status`, `hanger_status`, `alarm_status`, `temp_status`, `last_update`) VALUES
(90, 'AA123', 'Closed', '', 'Down', 'Working', 14, '2016-07-21 11:49:43'),
(91, 'AA123', 'Open', '', 'Down', 'Working', 14, '2016-07-21 11:50:02'),
(92, 'AA123', 'Open', '', 'Down', 'Working', 14, '2016-07-21 13:10:49'),
(93, 'AA123', 'Open', '', 'Down', 'Working', 14, '2016-07-21 13:35:57'),
(94, 'AA123', 'Open', '', 'Down', 'Working', 14, '2016-07-21 13:37:54'),
(95, 'AA123', 'Closed', '', 'Down', 'Working', 14, '2016-07-21 14:03:36'),
(100, 'AA123', 'Open', '', 'Down', 'Working', 14, '2016-07-21 14:15:29'),
(102, 'AA123', 'Open', '', 'Up', 'Working', 14, '2016-07-21 14:16:57'),
(103, 'AA123', 'Open', '', 'Up', 'Fault', 14, '2016-07-21 14:17:06'),
(104, 'AA123', 'Open', '', 'Up', 'Fault', 14, '2016-07-21 14:18:26'),
(105, 'AA123', 'Closed', '', 'Down', 'Working', 14, '2016-07-21 14:18:43'),
(106, 'AA123', 'Closed', '', 'Down', 'Working', 14, '2016-07-21 14:43:22'),
(107, 'AA123', 'Open', '', 'Down', 'Working', 14, '2016-07-21 14:43:32');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `tbl_cabinets`
--
ALTER TABLE `tbl_cabinets`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `tbl_fleet`
--
ALTER TABLE `tbl_fleet`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `tbl_guardians`
--
ALTER TABLE `tbl_guardians`
  ADD PRIMARY KEY (`id`),
  ADD KEY `cabinet_id` (`cabinet_id`);

--
-- Indexes for table `tbl_status`
--
ALTER TABLE `tbl_status`
  ADD PRIMARY KEY (`id`),
  ADD KEY `cabinet_id` (`cabinet_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `tbl_fleet`
--
ALTER TABLE `tbl_fleet`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `tbl_guardians`
--
ALTER TABLE `tbl_guardians`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT for table `tbl_status`
--
ALTER TABLE `tbl_status`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=108;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `tbl_guardians`
--
ALTER TABLE `tbl_guardians`
  ADD CONSTRAINT `tbl_guardians_ibfk_1` FOREIGN KEY (`cabinet_id`) REFERENCES `tbl_cabinets` (`id`);

--
-- Constraints for table `tbl_status`
--
ALTER TABLE `tbl_status`
  ADD CONSTRAINT `tbl_status_ibfk_1` FOREIGN KEY (`cabinet_id`) REFERENCES `tbl_cabinets` (`id`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
