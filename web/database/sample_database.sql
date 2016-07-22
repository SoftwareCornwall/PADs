-- phpMyAdmin SQL Dump
-- version 4.5.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Jul 22, 2016 at 12:57 PM
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
('AA123', 'Gateway Business Center, Redruth', 'TR15 1SS'),
('AB123', 'Somewhere, Bude', 'TC83 KD3'),
('BB123', 'Somewhere, Truro', 'TR11 1UR');

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

--
-- Dumping data for table `tbl_fleet`
--

INSERT INTO `tbl_fleet` (`id`, `first_name`, `last_name`, `phone_number`) VALUES
(1, 'Jon', 'Cole', '+447477681144');

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
(1, 'AA123', 'Tyler', 'Arnold', '+447597997201');

-- --------------------------------------------------------

--
-- Table structure for table `tbl_status`
--

CREATE TABLE `tbl_status` (
  `id` int(11) NOT NULL,
  `cabinet_id` varchar(200) NOT NULL,
  `door_open` tinyint(1) NOT NULL,
  `defib_removed` tinyint(1) NOT NULL,
  `alarm_status` tinyint(1) NOT NULL,
  `temp_status` int(11) NOT NULL,
  `last_update` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `tbl_status`
--

INSERT INTO `tbl_status` (`id`, `cabinet_id`, `door_open`, `defib_removed`, `alarm_status`, `temp_status`, `last_update`) VALUES
(1, 'AA123', 0, 0, 0, 14, '2016-07-22 08:46:29'),
(2, 'AB123', 0, 0, 0, 14, '2016-07-22 08:46:57'),
(3, 'BB123', 0, 0, 0, 16, '2016-07-22 08:47:44'),
(4, 'AB123', 1, 0, 0, 16, '2016-07-22 08:48:00'),
(5, 'AB123', 1, 1, 0, 16, '2016-07-22 08:48:08'),
(6, 'AA123', 1, 0, 0, 15, '2016-07-22 09:29:16'),
(7, 'AA123', 0, 0, 0, 12, '2016-07-22 10:08:26'),
(8, 'AA123', 1, 1, 0, 15, '2016-07-22 10:11:03'),
(9, 'AA123', 1, 0, 0, 15, '2016-07-22 10:11:17'),
(10, 'AA123', 1, 1, 0, 15, '2016-07-22 10:11:45'),
(11, 'AA123', 1, 0, 0, 15, '2016-07-22 10:13:20'),
(12, 'AA123', 1, 0, 0, 15, '2016-07-22 10:13:50'),
(13, 'AA123', 0, 0, 0, 12, '2016-07-22 10:15:30'),
(14, 'AA123', 1, 0, 0, 15, '2016-07-22 10:15:58'),
(15, 'AA123', 1, 0, 0, 15, '2016-07-22 10:16:28'),
(16, 'AA123', 1, 1, 0, 15, '2016-07-22 10:22:02'),
(17, 'AA123', 0, 0, 0, 12, '2016-07-22 10:27:58'),
(18, 'AA123', 0, 0, 0, 12, '2016-07-22 10:32:57');

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
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `tbl_guardians`
--
ALTER TABLE `tbl_guardians`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT for table `tbl_status`
--
ALTER TABLE `tbl_status`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=19;
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
