-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 11, 2025 at 09:03 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `restaurant_global_fastfood2`
--

-- --------------------------------------------------------

--
-- Table structure for table `angajati`
--

CREATE TABLE `angajati` (
  `id_ang` int(11) NOT NULL,
  `nume` varchar(50) DEFAULT NULL,
  `prenume` varchar(50) DEFAULT NULL,
  `functie` varchar(50) DEFAULT NULL,
  `telefon` int(10) DEFAULT NULL,
  `id_res` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `angajati`
--

INSERT INTO `angajati` (`id_ang`, `nume`, `prenume`, `functie`, `telefon`, `id_res`) VALUES
(1, 'Silvica', 'Robert ', 'Manager', 771543798, 101),
(2, 'Ardeleanu', 'Madalina', 'Manager', 77589463, 102),
(3, 'Moldovan', 'Florin', 'Manager', 761778943, 103),
(4, 'Popescu', 'Marius ', 'Manager', 745262718, 104),
(5, 'Vasile', 'Marian', 'Manager', 725212712, 105),
(6, 'Vasile', 'Maxim', 'Chelner', 77546789, 101),
(7, 'Andrei', 'Silviu', 'Chelner', 771675893, 101),
(8, 'Popescu', 'Stanciulescu', 'Chelner', 761783465, 101),
(9, 'Dan', 'Leustean', 'Chelner', 789354675, 101),
(10, 'Costi', 'Max', 'Chelner', 77546789, 102),
(11, 'Andrei', 'Selaru', 'Chelner', 771675893, 102),
(12, 'Tina', 'Duceag', 'Chelner', 761783465, 102),
(13, 'Albert', 'Popescu', 'Chelner', 789354675, 102),
(14, 'Liviu', 'Maximus', 'Chelner', 77546789, 103),
(15, 'Andrei', 'Valeriu', 'Chelner', 771675893, 103),
(16, 'David', 'Paun', 'Chelner', 761783465, 103),
(17, 'Silviu', 'Andronache', 'Chelner', 789354675, 103),
(18, 'Alexandru', 'Viteazu', 'Chelner', 77546789, 104),
(19, 'Andrei', 'Naxis', 'Chelner', 771675893, 104),
(20, 'Popescu', 'Ionica', 'Chelner', 761783465, 104),
(21, 'Dan', 'Mogosanu', 'Chelner', 789354675, 104),
(22, 'Vasile', 'Mamistru', 'Chelner', 77546789, 105),
(23, 'Liviu', 'Silviu', 'Chelner', 771675893, 105),
(24, 'Popescu', 'Georgescu', 'Chelner', 761783465, 105),
(25, 'Alexandru', 'Leustean', 'Chelner', 789354675, 105),
(26, 'Alexandru', 'Matache', 'Bucatar', 785786456, 101),
(27, 'Liviu', 'Marius', 'Bucatar', 785786456, 101),
(28, 'Alex', 'Radulescu', 'Bucatar', 785786456, 102),
(29, 'Alex', 'Tranca', 'Bucatar', 785786456, 102),
(30, 'Costache', 'Matache', 'Bucatar', 785786456, 103),
(31, 'Andreea', 'Vldischi', 'Bucatar', 785786456, 103),
(32, 'Charles', 'Lecler', 'Bucatar', 785786456, 104),
(33, 'Lando', 'Noris', 'Bucatar', 785786456, 104),
(34, 'Lewis', 'Hamilton', 'Bucatar', 785786456, 105),
(35, 'Liviu', 'Zara', 'Bucatar', 785786456, 105),
(36, 'Alexandru', 'Matache', 'Curatenie', 785786456, 101),
(37, 'Alex', 'Coximus', 'Curatenie', 785786456, 101),
(38, 'Ana', 'Matici', 'Curatenie', 785786456, 102),
(39, 'Ioana', 'Sfinxu', 'Curatenie', 785786456, 102),
(40, 'Andrei', 'Gavril', 'Curatenie', 785786456, 103),
(41, 'Petrut', 'Bisoi', 'Curatenie', 785786456, 103),
(42, 'Andrei', 'Zbir', 'Curatenie', 785786456, 104),
(43, 'BAT', 'MAN', 'Curatenie', 785786456, 104),
(44, 'Alexndru', 'Zbarnoaia', 'Curatenie', 785786456, 105),
(45, 'Hasilnus', 'Coprate', 'Curatenie', 785786456, 105);

-- --------------------------------------------------------

--
-- Table structure for table `card_fidelitate`
--

CREATE TABLE `card_fidelitate` (
  `id_card` int(11) NOT NULL,
  `id_client` int(11) DEFAULT NULL,
  `mancare_preferata` varchar(50) DEFAULT NULL,
  `puncte_acumulate` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `card_fidelitate`
--

INSERT INTO `card_fidelitate` (`id_card`, `id_client`, `mancare_preferata`, `puncte_acumulate`) VALUES
(1, 3, 'Pizza', 1450),
(2, 5, 'Burgeri Kong', 2000),
(3, 7, 'Paste', 320),
(4, 10, 'Sopapilla', 1800),
(5, 12, 'Chicken Mole', 2700),
(6, 15, 'Noodles', 1350),
(7, 18, 'Sarmale', 800),
(8, 21, 'Pizza', 2200),
(9, 23, 'Burgeri Kong', 2900),
(10, 26, 'Chicken Mole', 1000),
(11, 28, 'Sopapilla', 400),
(12, 30, 'Paste', 2500),
(13, 33, 'Noodles', 1850),
(14, 36, 'Sarmale', 700),
(15, 38, 'Pizza', 3000),
(16, 40, 'Burgeri Kong', 1400),
(17, 42, 'Chicken Mole', 270),
(18, 44, 'Sopapilla', 1000),
(19, 45, 'Paste', 2400),
(20, 46, 'Noodles', 1900),
(21, 48, 'Sarmale', 1500),
(22, 50, 'Pizza', 600),
(23, 2, 'Burgeri Kong', 1750),
(24, 4, 'Chicken Mole', 250),
(25, 6, 'Sopapilla', 2900);

-- --------------------------------------------------------

--
-- Table structure for table `clienti`
--

CREATE TABLE `clienti` (
  `id_client` int(11) NOT NULL,
  `nume` varchar(50) DEFAULT NULL,
  `prenume` varchar(50) DEFAULT NULL,
  `telefon` int(11) DEFAULT NULL,
  `email` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `clienti`
--

INSERT INTO `clienti` (`id_client`, `nume`, `prenume`, `telefon`, `email`) VALUES
(1, 'Popescu', 'Ion', 723456789, 'ion.popescu@gmail.com'),
(2, 'Ionescu', 'Maria', 721123456, 'maria.ionescu@yahoo.com'),
(3, 'Georgescu', 'Andrei', 745567890, 'andrei.georgescu@gmail.com'),
(4, 'Dumitrescu', 'Elena', 734987654, 'elena.dumitrescu@gmail.com'),
(5, 'Vasilescu', 'Mihai', 729987123, 'mihai.vasilescu@gmail.com'),
(6, 'Stan', 'Ana', 732456789, 'ana.stan@yahoo.com'),
(7, 'Radu', 'Cristina', 746123456, 'cristina.radu@gmail.com'),
(8, 'Popa', 'Adrian', 721345678, 'adrian.popa@gmail.com'),
(9, 'Ilie', 'Raluca', 732123456, 'raluca.ilie@gmail.com'),
(10, 'Constantinescu', 'Daniel', 745987123, 'daniel.constantinescu@yahoo.com'),
(11, 'Mihai', 'Alexandra', 732459876, 'alexandra.mihai@gmail.com'),
(12, 'Dobre', 'Florin', 723345678, 'florin.dobre@gmail.com'),
(13, 'Petrescu', 'Ioana', 734567890, 'ioana.petrescu@yahoo.com'),
(14, 'Gheorghe', 'Razvan', 746789123, 'razvan.gheorghe@gmail.com'),
(15, 'Tudor', 'Mirela', 734987654, 'mirela.tudor@yahoo.com'),
(16, 'Barbu', 'Victor', 729987123, 'victor.barbu@gmail.com'),
(17, 'Lupu', 'Diana', 732123456, 'diana.lupu@gmail.com'),
(18, 'Marin', 'Sorin', 745567890, 'sorin.marin@yahoo.com'),
(19, 'Chirila', 'Oana', 721123456, 'oana.chirila@gmail.com'),
(20, 'Neagu', 'Alexandru', 732456789, 'alexandru.neagu@gmail.com'),
(21, 'Iancu', 'Monica', 746123456, 'monica.iancu@gmail.com'),
(22, 'Enache', 'Roxana', 733345678, 'roxana.enache@gmail.com'),
(23, 'Filip', 'Gabriel', 721345678, 'gabriel.filip@yahoo.com'),
(24, 'Voicu', 'Bianca', 732123456, 'bianca.voicu@gmail.com'),
(25, 'Baciu', 'Marius', 744987654, 'marius.baciu@gmail.com'),
(26, 'Nicolae', 'Loredana', 729987123, 'loredana.nicolae@gmail.com'),
(27, 'Grigore', 'Adelina', 732123456, 'adelina.grigore@yahoo.com'),
(28, 'Olteanu', 'Sebastian', 745567890, 'sebastian.olteanu@gmail.com'),
(29, 'Zamfir', 'Andreea', 721123456, 'andreea.zamfir@gmail.com'),
(30, 'Roman', 'Bogdan', 732456789, 'bogdan.roman@yahoo.com'),
(31, 'Ciobanu', 'Carla', 746123456, 'carla.ciobanu@gmail.com'),
(32, 'Oprea', 'Lucian', 733345678, 'lucian.oprea@gmail.com'),
(33, 'Sava', 'Corina', 721345678, 'corina.sava@yahoo.com'),
(34, 'Cristea', 'Dragos', 732123456, 'dragos.cristea@gmail.com'),
(35, 'Mitrea', 'Denisa', 744987654, 'denisa.mitrea@gmail.com'),
(36, 'Parvu', 'Catalin', 729987123, 'catalin.parvu@gmail.com'),
(37, 'Stoica', 'Teodora', 732123456, 'teodora.stoica@gmail.com'),
(38, 'Dragan', 'George', 745567890, 'george.dragan@gmail.com'),
(39, 'Moise', 'Ramona', 721123456, 'ramona.moise@gmail.com'),
(40, 'Andrei', 'Florina', 732456789, 'florina.andrei@gmail.com'),
(41, 'Ganea', 'Paul', 746123456, 'paul.ganea@gmail.com'),
(42, 'Vlad', 'Anca', 733345678, 'anca.vlad@yahoo.com'),
(43, 'Simion', 'Stefan', 721345678, 'stefan.simion@gmail.com'),
(44, 'Boariu', 'Laura', 732123456, 'laura.boariu@gmail.com'),
(45, 'Muresan', 'Ioan', 744987654, 'ioan.muresan@yahoo.com'),
(46, 'Stanciu', 'Emil', 729987123, 'emil.stanciu@gmail.com'),
(47, 'Avram', 'Claudia', 732123456, 'claudia.avram@gmail.com'),
(48, 'Serban', 'Cosmin', 745567890, 'cosmin.serban@gmail.com'),
(49, 'Ene', 'Roxana', 721123456, 'roxana.ene@gmail.com'),
(50, 'Cojocaru', 'Alina', 732456789, 'alina.cojocaru@gmail.com');

-- --------------------------------------------------------

--
-- Table structure for table `evid_cas`
--

CREATE TABLE `evid_cas` (
  `id_cas` int(11) NOT NULL,
  `id_res` int(11) DEFAULT NULL,
  `data` date DEFAULT NULL,
  `suma` int(10) DEFAULT NULL,
  `euro` decimal(10,1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `evid_cas`
--

INSERT INTO `evid_cas` (`id_cas`, `id_res`, `data`, `suma`, `euro`) VALUES
(1, 101, '2023-04-13', 497366, 99473.2),
(2, 102, '2023-04-13', 457210, 91442.0),
(3, 103, '2023-04-13', 437342, 87468.4),
(4, 104, '2023-04-13', 510330, 102066.0),
(5, 105, '2023-04-13', 499999, 99999.8);

-- --------------------------------------------------------

--
-- Table structure for table `evid_comenzilor`
--

CREATE TABLE `evid_comenzilor` (
  `id_com` int(11) NOT NULL,
  `id_res` int(11) DEFAULT NULL,
  `id_meniu` int(11) DEFAULT NULL,
  `id_ang` int(11) DEFAULT NULL,
  `id_client` int(11) DEFAULT NULL,
  `pret` decimal(10,2) DEFAULT NULL,
  `tips` decimal(10,2) DEFAULT NULL,
  `data_comanda` datetime DEFAULT NULL,
  `cadou` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `evid_comenzilor`
--

INSERT INTO `evid_comenzilor` (`id_com`, `id_res`, `id_meniu`, `id_ang`, `id_client`, `pret`, `tips`, `data_comanda`, `cadou`) VALUES
(0, 101, 1002, 6, 25, NULL, NULL, '2023-05-21 23:00:00', NULL),
(1, 101, 1001, 6, 25, 37.00, 3.70, '2023-04-14 22:00:00', NULL),
(3, 102, 1002, 7, 2, 55.00, 5.50, '2023-04-30 10:00:00', NULL),
(4, 103, 1004, 8, 9, 35.00, 3.50, '2023-05-22 09:00:00', NULL),
(5, 105, 1005, 15, 30, 35.00, 3.50, '2023-05-02 05:00:00', NULL),
(6, 104, 1007, 14, 29, 36.00, 3.60, '2023-05-02 08:00:00', NULL),
(7, 104, 1003, 9, 24, 27.00, 2.70, '2023-05-21 18:00:00', NULL),
(8, 101, 1002, 6, 1, 37.00, 3.70, '2023-04-16 12:00:00', 'Cutie de bomboane'),
(9, 103, 1003, 8, 13, 30.00, 3.00, '2023-05-01 21:00:00', NULL),
(10, 102, 1001, 7, 16, 22.00, 2.20, '2023-04-16 12:00:00', 'Cutie de bomboane'),
(11, 105, 1002, 10, 22, 35.00, 3.50, '2023-04-19 17:00:00', NULL),
(12, 101, 1003, 6, 5, 55.00, 5.50, '2023-04-24 18:00:00', NULL),
(13, 103, 1004, 9, 19, 35.00, 3.50, '2023-05-21 08:00:00', NULL),
(14, 104, 1005, 12, 23, 35.00, 3.50, '2023-05-14 04:00:00', NULL),
(15, 105, 1007, 14, 18, 36.00, 3.60, '2023-05-23 10:00:00', NULL),
(16, 101, 1008, 6, 11, 27.00, 2.70, '2023-04-16 14:00:00', 'Voucher reducere'),
(17, 102, 1009, 7, 12, 37.00, 3.70, '2023-04-16 05:00:00', NULL),
(18, 104, 1010, 15, 17, 30.00, 3.00, '2023-05-07 04:00:00', NULL),
(19, 101, 1001, 6, 21, 22.00, 2.20, '2023-05-10 13:00:00', NULL),
(20, 102, 1002, 12, 25, 35.00, 3.50, '2023-05-06 05:00:00', NULL),
(21, 103, 1003, 7, 8, 55.00, 5.50, '2023-05-16 04:00:00', NULL),
(22, 104, 1004, 9, 27, 35.00, 3.50, '2023-04-25 13:00:00', NULL),
(23, 105, 1002, 10, 1, 35.00, 3.50, '2023-04-17 12:00:00', NULL),
(24, 101, 1007, 6, 22, 36.00, 3.60, '2023-05-09 06:00:00', NULL),
(25, 102, 1008, 11, 28, 27.00, 2.70, '2023-05-17 03:00:00', NULL),
(26, 103, 1009, 8, 30, 37.00, 3.70, '2023-04-21 06:00:00', NULL),
(27, 104, 1010, 15, 5, 30.00, 3.00, '2023-05-04 21:00:00', NULL),
(28, 101, 1003, 6, 9, 22.00, 2.20, '2023-04-13 23:00:00', NULL),
(29, 102, 1003, 7, 6, 35.00, 3.50, '2023-05-05 07:00:00', NULL),
(30, 103, 1003, 8, 19, 55.00, 5.50, '2023-05-07 19:00:00', NULL),
(31, 104, 1004, 9, 12, 35.00, 3.50, '2023-04-28 04:00:00', NULL),
(32, 105, 1005, 10, 21, 35.00, 3.50, '2023-04-14 05:00:00', NULL),
(33, 101, 1007, 6, 7, 36.00, 3.60, '2023-04-14 21:00:00', NULL),
(34, 102, 1008, 11, 14, 27.00, 2.70, '2023-04-18 09:00:00', NULL),
(35, 103, 1009, 8, 17, 37.00, 3.70, '2023-05-03 22:00:00', NULL),
(36, 104, 1010, 12, 22, 30.00, 3.00, '2023-04-17 20:00:00', NULL),
(37, 101, 1001, 6, 28, 22.00, 2.20, '2023-04-15 20:00:00', NULL),
(38, 102, 1002, 7, 4, 35.00, 3.50, '2023-05-23 23:00:00', NULL),
(39, 103, 1003, 8, 31, 55.00, 5.50, '2023-05-12 10:00:00', NULL),
(40, 104, 1004, 9, 2, 35.00, 3.50, '2023-05-06 18:00:00', NULL),
(41, 105, 1005, 10, 18, 35.00, 3.50, '2023-05-13 06:00:00', NULL),
(42, 101, 1007, 6, 26, 36.00, 3.60, '2023-05-20 23:00:00', NULL),
(43, 102, 1008, 11, 8, 27.00, 2.70, '2023-04-28 10:00:00', NULL),
(44, 103, 1009, 8, 10, 37.00, 3.70, '2023-04-17 12:00:00', NULL),
(45, 104, 1010, 15, 9, 30.00, 3.00, '2023-04-30 17:00:00', NULL),
(46, 101, 1003, 6, 3, 22.00, 2.20, '2023-05-16 02:00:00', NULL),
(47, 102, 1002, 7, 12, 35.00, 3.50, '2023-05-11 14:00:00', NULL),
(48, 103, 1003, 8, 21, 55.00, 5.50, '2023-04-14 19:00:00', NULL),
(49, 104, 1004, 9, 24, 35.00, 3.50, '2023-04-19 04:00:00', NULL),
(50, 105, 1005, 10, 19, 35.00, 3.50, '2023-05-08 03:00:00', NULL),
(51, 101, 1007, 6, 30, 36.00, 3.60, '2023-05-06 12:00:00', NULL),
(52, 102, 1008, 11, 17, 27.00, 2.70, '2023-05-24 18:00:00', NULL),
(53, 103, 1009, 8, 6, 37.00, 3.70, '2023-04-25 23:00:00', NULL),
(54, 104, 1010, 15, 14, 30.00, 3.00, '2023-05-05 12:00:00', NULL),
(55, 101, 1001, 6, 4, 22.00, 2.20, '2023-05-14 17:00:00', NULL),
(56, 102, 1002, 7, 11, 35.00, 3.50, '2023-04-20 10:00:00', NULL),
(57, 103, 1003, 8, 14, 55.00, 5.50, '2023-05-07 21:00:00', NULL),
(58, 104, 1004, 9, 27, 35.00, 3.50, '2023-05-01 15:00:00', NULL),
(59, 105, 1005, 10, 22, 35.00, 3.50, '2023-05-01 01:00:00', NULL),
(60, 101, 1007, 6, 15, 36.00, 3.60, '2023-05-17 02:00:00', NULL),
(61, 102, 1008, 11, 12, 27.00, 2.70, '2023-05-15 14:00:00', NULL),
(62, 103, 1003, 8, 17, 37.00, 3.70, '2023-05-01 17:00:00', NULL),
(63, 104, 1010, 12, 13, 30.00, 3.00, '2023-05-20 04:00:00', NULL),
(64, 101, 1001, 6, 24, 22.00, 2.20, '2023-04-17 08:00:00', NULL),
(65, 102, 1002, 7, 30, 35.00, 3.50, '2023-05-17 21:00:00', NULL),
(66, 103, 1003, 8, 9, 55.00, 5.50, '2023-05-19 04:00:00', NULL),
(67, 104, 1004, 9, 10, 35.00, 3.50, '2023-05-17 03:00:00', NULL),
(68, 105, 1005, 10, 5, 35.00, 3.50, '2023-05-03 05:00:00', NULL),
(69, 101, 1007, 6, 19, 36.00, 3.60, '2023-05-23 00:00:00', NULL),
(70, 102, 1008, 11, 26, 27.00, 2.70, '2023-04-27 02:00:00', NULL),
(71, 103, 1009, 8, 12, 37.00, 3.70, '2023-05-16 11:00:00', NULL),
(72, 104, 1010, 15, 14, 30.00, 3.00, '2023-05-24 09:00:00', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `furnizori`
--

CREATE TABLE `furnizori` (
  `Id_fur` int(11) NOT NULL,
  `nume` varchar(255) NOT NULL,
  `tara` enum('Romania','Italia','America','China','Korea') NOT NULL,
  `adresa` varchar(255) DEFAULT NULL,
  `numar_telefon` varchar(15) DEFAULT NULL,
  `email` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `furnizori`
--

INSERT INTO `furnizori` (`Id_fur`, `nume`, `tara`, `adresa`, `numar_telefon`, `email`) VALUES
(1, 'Global Supply Co.', 'Romania', 'Strada Exemplar 12, București', '0212345678', 'info@globalsupplyco.com'),
(2, 'FreshFoods Distributors', 'Italia', 'Via Roma 34, Roma', '0391234567', 'support@freshfoodsdistributors.org'),
(3, 'International Food Imports', 'America', '5th Avenue, New York', '00123456789', 'orders@internationalfoodimports.com'),
(4, 'Sunny Valley Imports', 'China', 'Beijing Street 101', '0101234567', 'contact@sunnyvalleyimports.org'),
(5, 'Optima Wholesale', 'Korea', 'Seoul, Gangnam District', '02-1234-5678', 'support@optimawholesale.biz');

-- --------------------------------------------------------

--
-- Table structure for table `meniu`
--

CREATE TABLE `meniu` (
  `id_meniu` int(11) NOT NULL,
  `nume` varchar(50) DEFAULT NULL,
  `pret` decimal(10,2) DEFAULT NULL,
  `disponibilitate` varchar(50) DEFAULT NULL,
  `mancare` varchar(50) DEFAULT NULL,
  `garnitura` varchar(50) DEFAULT NULL,
  `bautura` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `meniu`
--

INSERT INTO `meniu` (`id_meniu`, `nume`, `pret`, `disponibilitate`, `mancare`, `garnitura`, `bautura`) VALUES
(1001, 'mic dejun', 22.00, '8:00 AM - 11:00 AM', 'Omleta', 'Bacon', 'Suc de Portocale'),
(1002, 'pranz', 35.00, '11:01 AM - 00:00 AM', 'Ceafa de Porc', 'Cartofi Prajiti', 'Coca-Cola'),
(1003, 'burgeri kong', 55.00, '11:01 AM - 00:00 AM', 'Burger Kong', 'Cartofi Prajiti', 'Coca-Cola'),
(1004, 'chicken mole', 35.00, '11:01 AM - 00:00 AM', 'chicken mole', 'Orez', 'Coca-Cola'),
(1005, 'sopapilla', 35.00, '11:01 AM - 00:00 AM', 'sopapilla', NULL, NULL),
(1006, 'prajitura luna', 0.00, '8:00 AM - 00:00 AM', 'prajitura luna', NULL, NULL),
(1007, 'pizza', 36.00, '11:01 AM - 00:00 AM', 'pizza napoli', NULL, 'Coca-Cola'),
(1008, 'paste', 27.00, '11:01 AM - 00:00 AM', 'paste carbonara', NULL, NULL),
(1009, 'Noodles', 37.00, '11:01 AM - 00:00 AM', 'Ramen Noodles', NULL, NULL),
(1010, 'Sarmale', 30.00, '11:01 AM - 00:00 AM', '3 Sarmale', 'Smantana', NULL),
(1011, 'Anului Nou', 67.00, '00:00 AM - 23:59 PM', 'Somon', 'Orez', 'Coca-Cola');

-- --------------------------------------------------------

--
-- Table structure for table `produse`
--

CREATE TABLE `produse` (
  `id_prod` int(11) NOT NULL,
  `nume` varchar(255) DEFAULT NULL,
  `pret_unitate` decimal(10,2) DEFAULT NULL,
  `id_fur` int(11) DEFAULT NULL,
  `id_res` int(11) DEFAULT NULL,
  `cantitate` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `produse`
--

INSERT INTO `produse` (`id_prod`, `nume`, `pret_unitate`, `id_fur`, `id_res`, `cantitate`) VALUES
(15, 'Faina', 5.00, 1, 101, 100),
(16, 'Varza', 3.00, 2, 102, 150),
(17, 'Carne', 20.00, 3, 103, 80),
(18, 'Cartofi', 2.50, 4, 104, 200),
(19, 'Coca Cola', 8.00, 5, 105, 50),
(20, 'Zahar', 4.00, 1, 101, 120),
(21, 'Malai', 6.00, 2, 102, 90),
(22, 'Pizza', 15.00, 3, 103, 70),
(23, 'Paste', 12.00, 4, 104, 60),
(24, 'Sarmale', 10.00, 5, 105, 40);

-- --------------------------------------------------------

--
-- Table structure for table `restaurante`
--

CREATE TABLE `restaurante` (
  `id_res` int(11) NOT NULL,
  `tara` varchar(50) DEFAULT NULL,
  `oras` varchar(50) DEFAULT NULL,
  `adresa` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `restaurante`
--

INSERT INTO `restaurante` (`id_res`, `tara`, `oras`, `adresa`) VALUES
(101, 'Romania', 'Cluj-Napoca', 'Strada Albiei nr. 8'),
(102, 'Italia', 'Monza', 'Via Vetta d`Italia 2'),
(103, 'Anglia', 'Silverstone', '5 Whittlebury Rd'),
(104, 'Germania', 'Nürburg', 'Otto-Flimm-Straße'),
(105, 'Franta', 'Le Castellet', '2760 Rte des Hauts du Camp');

-- --------------------------------------------------------

--
-- Table structure for table `salarii_angajati`
--

CREATE TABLE `salarii_angajati` (
  `id_sal` int(11) NOT NULL,
  `id_ang` int(11) DEFAULT NULL,
  `data_plati` date DEFAULT NULL,
  `suma` int(11) DEFAULT NULL,
  `bonus` int(11) DEFAULT NULL,
  `salariu_net` int(11) DEFAULT NULL,
  `euro` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `salarii_angajati`
--

INSERT INTO `salarii_angajati` (`id_sal`, `id_ang`, `data_plati`, `suma`, `bonus`, `salariu_net`, `euro`) VALUES
(1, 1, '2023-04-13', 10000, 1000, 11000, 2200),
(2, 2, '2023-04-13', 10000, 1000, 11000, 2200),
(3, 3, '2023-04-13', 10000, 1000, 11000, 2200),
(4, 4, '2023-04-13', 10000, 1000, 11000, 2200),
(5, 5, '2023-04-13', 10000, 1000, 11000, 2200),
(6, 6, '2023-04-13', 4000, 300, 4300, 860),
(7, 7, '2023-04-13', 4000, 200, 4200, 840),
(8, 8, '2023-04-13', 4000, 145, 4145, 829),
(9, 9, '2023-04-13', 4000, 50, 4050, 810),
(10, 10, '2023-04-13', 4000, 300, 4300, 860),
(11, 11, '2023-04-13', 4000, 200, 4200, 840),
(12, 12, '2023-04-13', 4000, 145, 4145, 829),
(13, 13, '2023-04-13', 4000, 50, 4050, 810),
(14, 14, '2023-04-13', 4000, 150, 4150, 830),
(15, 15, '2023-04-13', 4000, 75, 4075, 815),
(16, 16, '2023-04-13', 4000, 175, 4175, 835),
(17, 17, '2023-04-13', 4000, 186, 4186, 837),
(18, 18, '2023-04-13', 4000, 150, 4150, 830),
(19, 19, '2023-04-13', 4000, 250, 4250, 850),
(20, 20, '2023-04-13', 4000, 350, 4350, 870),
(21, 21, '2023-04-13', 4000, 450, 4450, 890),
(22, 22, '2023-04-13', 4000, 250, 4250, 850),
(23, 23, '2023-04-13', 4000, 150, 4150, 830),
(24, 24, '2023-04-13', 4000, 550, 4550, 910),
(25, 25, '2023-04-13', 4000, 450, 4450, 890),
(26, 26, '2023-04-13', 7500, 500, 8000, 1600),
(27, 27, '2023-04-13', 7500, 500, 8000, 1600),
(28, 28, '2023-04-13', 7500, 200, 7700, 1540),
(29, 29, '2023-04-13', 7500, 300, 7800, 1560),
(30, 30, '2023-04-13', 7500, 285, 7785, 1557),
(31, 31, '2023-04-13', 7500, 600, 8100, 1620),
(32, 32, '2023-04-13', 7500, 700, 8200, 1640),
(33, 33, '2023-04-13', 7500, 100, 7600, 1520),
(34, 34, '2023-04-13', 7500, 300, 7800, 1560),
(35, 35, '2023-04-13', 7500, 200, 7700, 1540),
(36, 36, '2023-04-13', 2500, 200, 2700, 540),
(37, 37, '2023-04-13', 2500, 500, 3000, 600),
(38, 38, '2023-04-13', 2500, 800, 3300, 660),
(39, 39, '2023-04-13', 2500, 700, 3200, 640),
(40, 40, '2023-04-13', 2500, 500, 3000, 600),
(41, 41, '2023-04-13', 2500, 350, 2850, 570),
(42, 42, '2023-04-13', 2500, 1000, 3500, 700),
(43, 43, '2023-04-13', 2500, 700, 3200, 640),
(44, 44, '2023-04-13', 2500, 300, 2800, 560),
(45, 45, '2023-04-13', 2500, 650, 3150, 630);

-- --------------------------------------------------------

--
-- Table structure for table `ture`
--

CREATE TABLE `ture` (
  `id_ture` int(11) NOT NULL,
  `ora_inceput` varchar(50) DEFAULT NULL,
  `ora_sfarsit` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `ture`
--

INSERT INTO `ture` (`id_ture`, `ora_inceput`, `ora_sfarsit`) VALUES
(1, '8 AM', '4 PM'),
(2, '4 PM', '12 AM');

-- --------------------------------------------------------

--
-- Table structure for table `ture_angajati`
--

CREATE TABLE `ture_angajati` (
  `id_tura_ang` int(11) NOT NULL,
  `id_ang` int(11) DEFAULT NULL,
  `id_ture` int(11) DEFAULT NULL,
  `ore_lucrate` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `ture_angajati`
--

INSERT INTO `ture_angajati` (`id_tura_ang`, `id_ang`, `id_ture`, `ore_lucrate`) VALUES
(1, 1, 1, 170),
(2, 2, 1, 160),
(3, 3, 1, 180),
(4, 4, 1, 190),
(5, 5, 1, 165),
(6, 6, 1, 200),
(7, 7, 1, 175),
(8, 8, 2, 160),
(9, 9, 2, 185),
(10, 10, 1, 195),
(11, 11, 1, 170),
(12, 12, 2, 165),
(13, 13, 2, 180),
(14, 14, 1, 190),
(15, 15, 1, 200),
(16, 16, 2, 160),
(17, 17, 2, 175),
(18, 18, 1, 185),
(19, 19, 1, 165),
(20, 20, 2, 195),
(21, 21, 2, 200),
(22, 22, 1, 180),
(23, 23, 1, 170),
(24, 24, 2, 190),
(25, 25, 2, 160),
(26, 26, 1, 175),
(27, 27, 2, 185),
(28, 28, 1, 200),
(29, 29, 2, 165),
(30, 30, 1, 195),
(31, 31, 2, 180),
(32, 32, 1, 170),
(33, 33, 2, 160),
(34, 34, 1, 190),
(35, 35, 2, 175),
(36, 36, 1, 200),
(37, 37, 2, 165),
(38, 38, 1, 195),
(39, 39, 2, 185),
(40, 40, 1, 180),
(41, 41, 2, 170),
(42, 42, 1, 200),
(43, 43, 2, 190),
(44, 44, 1, 175),
(45, 45, 2, 165);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `angajati`
--
ALTER TABLE `angajati`
  ADD PRIMARY KEY (`id_ang`),
  ADD KEY `FK_id_res` (`id_res`);

--
-- Indexes for table `card_fidelitate`
--
ALTER TABLE `card_fidelitate`
  ADD PRIMARY KEY (`id_card`),
  ADD KEY `id_client` (`id_client`);

--
-- Indexes for table `clienti`
--
ALTER TABLE `clienti`
  ADD PRIMARY KEY (`id_client`);

--
-- Indexes for table `evid_cas`
--
ALTER TABLE `evid_cas`
  ADD PRIMARY KEY (`id_cas`),
  ADD KEY `id_res` (`id_res`);

--
-- Indexes for table `evid_comenzilor`
--
ALTER TABLE `evid_comenzilor`
  ADD PRIMARY KEY (`id_com`),
  ADD KEY `fk_restaurante` (`id_res`),
  ADD KEY `fk_meniu` (`id_meniu`),
  ADD KEY `fk_angajat` (`id_ang`),
  ADD KEY `fk_client` (`id_client`);

--
-- Indexes for table `furnizori`
--
ALTER TABLE `furnizori`
  ADD PRIMARY KEY (`Id_fur`);

--
-- Indexes for table `meniu`
--
ALTER TABLE `meniu`
  ADD PRIMARY KEY (`id_meniu`);

--
-- Indexes for table `produse`
--
ALTER TABLE `produse`
  ADD PRIMARY KEY (`id_prod`),
  ADD KEY `id_fur` (`id_fur`),
  ADD KEY `id_res` (`id_res`);

--
-- Indexes for table `restaurante`
--
ALTER TABLE `restaurante`
  ADD PRIMARY KEY (`id_res`);

--
-- Indexes for table `salarii_angajati`
--
ALTER TABLE `salarii_angajati`
  ADD PRIMARY KEY (`id_sal`),
  ADD KEY `id_ang` (`id_ang`);

--
-- Indexes for table `ture`
--
ALTER TABLE `ture`
  ADD PRIMARY KEY (`id_ture`);

--
-- Indexes for table `ture_angajati`
--
ALTER TABLE `ture_angajati`
  ADD PRIMARY KEY (`id_tura_ang`),
  ADD KEY `fk_id_ang` (`id_ang`),
  ADD KEY `fk_id_ture` (`id_ture`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `card_fidelitate`
--
ALTER TABLE `card_fidelitate`
  MODIFY `id_card` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=26;

--
-- AUTO_INCREMENT for table `evid_cas`
--
ALTER TABLE `evid_cas`
  MODIFY `id_cas` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `evid_comenzilor`
--
ALTER TABLE `evid_comenzilor`
  MODIFY `id_com` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=73;

--
-- AUTO_INCREMENT for table `furnizori`
--
ALTER TABLE `furnizori`
  MODIFY `Id_fur` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `produse`
--
ALTER TABLE `produse`
  MODIFY `id_prod` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=25;

--
-- AUTO_INCREMENT for table `salarii_angajati`
--
ALTER TABLE `salarii_angajati`
  MODIFY `id_sal` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=46;

--
-- AUTO_INCREMENT for table `ture_angajati`
--
ALTER TABLE `ture_angajati`
  MODIFY `id_tura_ang` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=47;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `angajati`
--
ALTER TABLE `angajati`
  ADD CONSTRAINT `FK_id_res` FOREIGN KEY (`id_res`) REFERENCES `restaurante` (`id_res`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `card_fidelitate`
--
ALTER TABLE `card_fidelitate`
  ADD CONSTRAINT `card_fidelitate_ibfk_1` FOREIGN KEY (`id_client`) REFERENCES `clienti` (`id_client`);

--
-- Constraints for table `evid_cas`
--
ALTER TABLE `evid_cas`
  ADD CONSTRAINT `evid_cas_ibfk_1` FOREIGN KEY (`id_res`) REFERENCES `restaurante` (`id_res`);

--
-- Constraints for table `evid_comenzilor`
--
ALTER TABLE `evid_comenzilor`
  ADD CONSTRAINT `fk_angajat` FOREIGN KEY (`id_ang`) REFERENCES `angajati` (`id_ang`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `fk_client` FOREIGN KEY (`id_client`) REFERENCES `clienti` (`id_client`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `fk_meniu` FOREIGN KEY (`id_meniu`) REFERENCES `meniu` (`id_meniu`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `fk_restaurante` FOREIGN KEY (`id_res`) REFERENCES `restaurante` (`id_res`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `produse`
--
ALTER TABLE `produse`
  ADD CONSTRAINT `produse_ibfk_1` FOREIGN KEY (`id_fur`) REFERENCES `furnizori` (`Id_fur`),
  ADD CONSTRAINT `produse_ibfk_2` FOREIGN KEY (`id_res`) REFERENCES `restaurante` (`id_res`);

--
-- Constraints for table `salarii_angajati`
--
ALTER TABLE `salarii_angajati`
  ADD CONSTRAINT `salarii_angajati_ibfk_1` FOREIGN KEY (`id_ang`) REFERENCES `angajati` (`id_ang`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `ture_angajati`
--
ALTER TABLE `ture_angajati`
  ADD CONSTRAINT `fk_id_ang` FOREIGN KEY (`id_ang`) REFERENCES `angajati` (`id_ang`),
  ADD CONSTRAINT `fk_id_ture` FOREIGN KEY (`id_ture`) REFERENCES `ture` (`id_ture`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
