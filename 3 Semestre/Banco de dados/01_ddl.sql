
CREATE TABLE brands (
  id_brand INT AUTO_INCREMENT PRIMARY KEY,
  brand_name VARCHAR(50) NOT NULL UNIQUE
);

CREATE TABLE fuel_types (
  id_fuel INT AUTO_INCREMENT PRIMARY KEY,
  fuel_type VARCHAR(20) NOT NULL UNIQUE
);

CREATE TABLE transmissions (
  id_trans INT AUTO_INCREMENT PRIMARY KEY,
  transmission_type VARCHAR(20) NOT NULL UNIQUE
);

CREATE TABLE models (
  id_model INT AUTO_INCREMENT PRIMARY KEY,
  model_name VARCHAR(50) NOT NULL,
  id_brand INT NOT NULL,
  FOREIGN KEY (id_brand) REFERENCES brands(id_brand),
  UNIQUE (model_name, id_brand)
);

CREATE TABLE cars (
  id_car INT AUTO_INCREMENT PRIMARY KEY,
  id_model INT NOT NULL,
  year INT NOT NULL,
  engine_size DECIMAL(3,1) NOT NULL,
  id_fuel INT NOT NULL,
  id_trans INT NOT NULL,
  mileage INT NOT NULL,
  doors INT NOT NULL,
  owner_count INT NOT NULL,
  price INT NOT NULL,
  FOREIGN KEY (id_model) REFERENCES models(id_model),
  FOREIGN KEY (id_fuel) REFERENCES fuel_types(id_fuel),
  FOREIGN KEY (id_trans) REFERENCES transmissions(id_trans)
);