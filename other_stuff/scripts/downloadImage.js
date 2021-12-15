const { exec } = require("child_process");


// Source: https://game8.co/games/Shin-Megami-Tensei-V/archives/348028
// Extracted using:
// document.querySelectorAll("a > img[width=\"140\"]").forEach(it => t.push({name: it.alt.replace(" icon", ""), url: it.src, race: it.parentElement.parentElement.parentElement.lastElementChild.textContent.trim()}));

const images = [
  {
    "name": "Slime",
    "url": "https://img.game8.co/3450183/9eeed97b29673776276563c0294fbdd1.jpeg/show",
    "race": "Foul"
  },
  {
    "name": "Pixie",
    "url": "https://img.game8.co/3450184/ccc8565f943b30d58a76b42938488c56.jpeg/show",
    "race": "Fairy"
  },
  {
    "name": "Preta",
    "url": "https://img.game8.co/3450185/f88506ed71fe8eed47cc047fc65ccda3.jpeg/show",
    "race": "Haunt"
  },
  {
    "name": "Onmoraki",
    "url": "https://img.game8.co/3450186/00298c1f47682b91b3287eae9a9fb59f.jpeg/show",
    "race": "Raptor"
  },
  {
    "name": "Mandrake",
    "url": "https://img.game8.co/3450190/86676cb7e3f7baa4afa539ece8d574fc.jpeg/show",
    "race": "Yoma"
  },
  {
    "name": "Sudama",
    "url": "https://img.game8.co/3450218/684dce82256ef334afaac661bc8d2eb0.jpeg/show",
    "race": "Jirae"
  },
  {
    "name": "Kodama",
    "url": "https://img.game8.co/3450189/614e20c92e90e486ed5321968d51f828.jpeg/show",
    "race": "Jirae"
  },
  {
    "name": "Daemon",
    "url": "https://img.game8.co/3450191/20259b12efc1de5a29ceba1cc7c2c952.jpeg/show",
    "race": "Brute"
  },
  {
    "name": "Cait Sith",
    "url": "https://img.game8.co/3450192/c54c06a2d37dcdc54358117d2458c1cf.jpeg/show",
    "race": "Beast"
  },
  {
    "name": "Sandman",
    "url": "https://img.game8.co/3450193/15dd1b1a2a35f4f000b8b3178317196d.jpeg/show",
    "race": "Night"
  },
  {
    "name": "Agathion",
    "url": "https://img.game8.co/3450196/4033f693756e2ce403ffffd265a911dc.jpeg/show",
    "race": "Yoma"
  },
  {
    "name": "Turdak",
    "url": "https://img.game8.co/3450200/e1003e6da1e2272ca95c73e9351673ba.jpeg/show",
    "race": "Jaki"
  },
  {
    "name": "Azumi",
    "url": "https://img.game8.co/3450198/0e9c3653eac97ecb24a8d7d8f4cc1dc5.jpeg/show",
    "race": "Brute"
  },
  {
    "name": "Obariyon",
    "url": "https://img.game8.co/3450201/de37d5eeeeeb6e31361f0316a7aaecfd.jpeg/show",
    "race": "Haunt"
  },
  {
    "name": "Tsuchigumo",
    "url": "https://img.game8.co/3450204/f5421e20ff8f317d5ca3aba96c6bc891.jpeg/show",
    "race": "Jirae"
  },
  {
    "name": "Bicorn",
    "url": "https://img.game8.co/3450206/ba71a1d674e15a435cf6c761ffe43726.jpeg/show",
    "race": "Wilder"
  },
  {
    "name": "Zhen",
    "url": "https://img.game8.co/3450210/c8626e13edb5ef221f8be4867373322e.jpeg/show",
    "race": "Raptor"
  },
  {
    "name": "Mokoi",
    "url": "https://img.game8.co/3450213/128c0d4c57bfc78643aaa561338b65b8.jpeg/show",
    "race": "Night"
  },
  {
    "name": "Aitvaras",
    "url": "https://img.game8.co/3450215/f350bc29c21d6e47b101aba3cbdf98dc.jpeg/show",
    "race": "Drake"
  },
  {
    "name": "Ippon-Datara",
    "url": "https://img.game8.co/3450216/3328018470de9281147224cce1042e05.jpeg/show",
    "race": "Brute"
  },
  {
    "name": "Andras",
    "url": "https://img.game8.co/3450219/9e77ec03a56686b104116d49a5f62528.jpeg/show",
    "race": "Fallen"
  },
  {
    "name": "Legion",
    "url": "https://img.game8.co/3450551/549ac492d47d1c812db8f9a847162109.jpeg/show",
    "race": "Foul"
  },
  {
    "name": "Rakshasa",
    "url": "https://img.game8.co/3450225/8086f74fc859f358e6a8bd472de367f1.jpeg/show",
    "race": "Jaki"
  },
  {
    "name": "Jack-",
    "url": "https://img.game8.co/3450226/2a75089b1513527c597fae8873cce9cf.jpeg/show",
    "race": "Fairy"
  },
  {
    "name": "Kaya-no-Hime",
    "url": "https://img.game8.co/3450227/df2ed3d0f312f244d0aee259d8b82364.jpeg/show",
    "race": "Jirae"
  },
  {
    "name": "Incubus",
    "url": "https://img.game8.co/3450229/3d42f8f408c7e981142b12c5ab71f40a.jpeg/show",
    "race": "Night"
  },
  {
    "name": "Oni",
    "url": "https://img.game8.co/3450233/846105e5bb178034d6ebb40e34d07a75.jpeg/show",
    "race": "Brute"
  },
  {
    "name": "Inugami",
    "url": "https://img.game8.co/3450238/e6e7d9d135adbdcb473cb08eca38f0ee.jpeg/show",
    "race": "Beast"
  },
  {
    "name": "Berith",
    "url": "https://img.game8.co/3450235/9b521dc8e4badd0e24069cf5f1cb7e20.jpeg/show",
    "race": "Fallen"
  },
  {
    "name": "Bugs",
    "url": "https://img.game8.co/3450237/b4cc0dd652ca097718ae4776291452bf.jpeg/show",
    "race": "Wilder"
  },
  {
    "name": "Koppa Tengu",
    "url": "https://img.game8.co/3450239/b41a328d293793a315fc107d12f8bae4.jpeg/show",
    "race": "Yoma"
  },
  {
    "name": "Jack Frost",
    "url": "https://img.game8.co/3450244/b33f15054ab2cff984d0375c69e3b27e.jpeg/show",
    "race": "Fairy"
  },
  {
    "name": "Manananggal",
    "url": "https://img.game8.co/3450243/d3520ae5e6470bb85226a9deea003d8c.jpeg/show",
    "race": "Femme"
  },
  {
    "name": "Poltergeist",
    "url": "https://img.game8.co/3450240/275c915584d7dffa887f4c427607ec37.jpeg/show",
    "race": "Haunt"
  },
  {
    "name": "Koropokkur",
    "url": "https://img.game8.co/3450252/7a39f5d92d209a75869c2e59764cc34a.jpeg/show",
    "race": "Jirae"
  },
  {
    "name": "Cironnup",
    "url": "https://img.game8.co/3450256/277538c551a645ca0149d06dc72c0e35.jpeg/show",
    "race": "Holy"
  },
  {
    "name": "Naga",
    "url": "https://img.game8.co/3450253/69aaf2dd2c7b4136691d8ca41dcd4435.jpeg/show",
    "race": "Snake"
  },
  {
    "name": "Mothman",
    "url": "https://img.game8.co/3450259/685548ad125ac9a47c44f2dcd3577fdb.jpeg/show",
    "race": "Wilder"
  },
  {
    "name": "Shiki-Ouji",
    "url": "https://img.game8.co/3450258/00d8e97daa64905f0cdfb00cb20368ad.jpeg/show",
    "race": "Brute"
  },
  {
    "name": "Loa",
    "url": "https://img.game8.co/3450283/b75b029770f840629d0e9f355148514f.jpeg/show",
    "race": "Jaki"
  },
  {
    "name": "Kelpie",
    "url": "https://img.game8.co/3450285/6fef50f5e5a07caf9ec483903caecd14.jpeg/show",
    "race": "Fairy"
  },
  {
    "name": "Yaksini",
    "url": "https://img.game8.co/3450260/32c1eabf93df91d178f6cfcfa26eabb4.jpeg/show",
    "race": "Femme"
  },
  {
    "name": "Basilisk",
    "url": "https://img.game8.co/3450287/5f1bc866a027851a470c1f07bce8db4b.jpeg/show",
    "race": "Drake"
  },
  {
    "name": "Hua Po",
    "url": "https://img.game8.co/3450289/0ec25a5ca80bfa036967fd645f026e1e.jpeg/show",
    "race": "Jirae"
  },
  {
    "name": "Forneus",
    "url": "https://img.game8.co/3450288/44f0af55f5c8a58e92c792b75f4d77ff.jpeg/show",
    "race": "Fallen"
  },
  {
    "name": "Pisaca",
    "url": "https://img.game8.co/3450286/ecce69445cd9144c6cbbe7d8f37a01b0.jpeg/show",
    "race": "Haunt"
  },
  {
    "name": "Lilim",
    "url": "https://img.game8.co/3450290/7e8dd74d74c5c74530862b45ef100958.jpeg/show",
    "race": "Night"
  },
  {
    "name": "Baphomet",
    "url": "https://img.game8.co/3450336/80494864422d2a01a66b22579a11d532.jpeg/show",
    "race": "Vile"
  },
  {
    "name": "Nekomata",
    "url": "https://img.game8.co/3450346/1191c6d818e56267802a832ec7ba1aec.jpeg/show",
    "race": "Beast"
  },
  {
    "name": "Setanta",
    "url": "https://img.game8.co/3450340/a27c9fb0a904c840f47aad51550b6891.jpeg/show",
    "race": "Fairy"
  },
  {
    "name": "Eligor",
    "url": "https://img.game8.co/3450343/36b1db13eff9d5cf1cb8cb2574918a09.jpeg/show",
    "race": "Fallen"
  },
  {
    "name": "Lamia",
    "url": "https://img.game8.co/3450339/801e97c7072dd4f3709725ecf40565c3.jpeg/show",
    "race": "Femme"
  },
  {
    "name": "Succubus",
    "url": "https://img.game8.co/3450342/d745e69080cb41af376633b692ea4b9f.jpeg/show",
    "race": "Night"
  },
  {
    "name": "Narcissus",
    "url": "https://img.game8.co/3450455/4b8655604177d364ea00cc12de5820f7.jpeg/show",
    "race": "Jirae"
  },
  {
    "name": "Kurama Tengu",
    "url": "https://img.game8.co/3450462/0f2114b1818cbbc3309eda84b60db687.jpeg/show",
    "race": "Genma"
  },
  {
    "name": "Naga Raja",
    "url": "https://img.game8.co/3450456/a047491e836a54a8f42d7cdd4b6565f3.jpeg/show",
    "race": "Snake"
  },
  {
    "name": "Valkyrie",
    "url": "https://img.game8.co/3450459/6ee57d0d4f66ec5b98f244fffa1c19bc.jpeg/show",
    "race": "Yoma"
  },
  {
    "name": "Kumbhanda",
    "url": "https://img.game8.co/3450473/6bb0bf1c2181822b83a8806f46efb8e4.jpeg/show",
    "race": "Haunt"
  },
  {
    "name": "Orthrus",
    "url": "https://img.game8.co/3450477/acf5c6a7b76fc2ce5d75e5dff6781e16.jpeg/show",
    "race": "Beast"
  },
  {
    "name": "Mishaguji",
    "url": "https://img.game8.co/3450480/9d9edc634687067f9915ff8e29192bdc.jpeg/show",
    "race": "Vile"
  },
  {
    "name": "Macabre",
    "url": "https://img.game8.co/3450478/5a2df90325801a6c76a76cf749957316.jpeg/show",
    "race": "Jaki"
  },
  {
    "name": "Ose",
    "url": "https://img.game8.co/3450487/ac3225569c7e2c082fd7cd2b998e8b10.jpeg/show",
    "race": "Fallen"
  },
  {
    "name": "Kaiwan",
    "url": "https://img.game8.co/3450484/c1a5d1bfd031fc066aa9b5198d1864f3.jpeg/show",
    "race": "Night"
  },
  {
    "name": "Dakini",
    "url": "https://img.game8.co/3450494/2d11413c448d1d505ba36af3146e7d8b.jpeg/show",
    "race": "Femme"
  },
  {
    "name": "Oberon",
    "url": "https://img.game8.co/3450493/6d68c3d60590e972b09079c332466a16.jpeg/show",
    "race": "Fairy"
  },
  {
    "name": "Anzu",
    "url": "https://img.game8.co/3450506/f63d3956abec436de9b437c0cc222f31.jpeg/show",
    "race": "Raptor"
  },
  {
    "name": "Loup-garou",
    "url": "https://img.game8.co/3453166/04ec9bd189cf29c205cfee8bb1e14914.jpeg/show",
    "race": "Beast"
  },
  {
    "name": "Decarabia",
    "url": "https://img.game8.co/3453036/1e50325b3a6f0c16d747fba956625b2f.jpeg/show",
    "race": "Fallen"
  },
  {
    "name": "Hecatoncheir",
    "url": "https://img.game8.co/3452917/c01308c1b5a98d4b5c301d484ad882f2.jpeg/show",
    "race": "Jaki"
  },
  {
    "name": "Queen Mab",
    "url": "https://img.game8.co/3453966/64c3af3f731189516429f82a3cab61fd.jpeg/show",
    "race": "Night"
  },
  {
    "name": "Sui-Ki",
    "url": "https://img.game8.co/3453972/89dd43cbb5e8b860cde04b565767b2e7.jpeg/show",
    "race": "Brute"
  },
  {
    "name": "Titania",
    "url": "https://img.game8.co/3453364/8a727b8a6498d2985594c919cda647af.jpeg/show",
    "race": "Fairy"
  },
  {
    "name": "Lachesis",
    "url": "https://img.game8.co/3453953/98d23ba6a848da8412872c3913b10545.jpeg/show",
    "race": "Femme"
  },
  {
    "name": "Fafnir",
    "url": "https://img.game8.co/3453339/ae87e63fa78c01669060e6d758bcbb8b.jpeg/show",
    "race": "Drake"
  },
  {
    "name": "Fuu-Ki",
    "url": "https://img.game8.co/3453895/10eb8428dd40340c6617900351e6c674.jpeg/show",
    "race": "Brute"
  },
  {
    "name": "Throne",
    "url": "https://img.game8.co/3453368/74093d74d8461f8184a39d536ee438dc.jpeg/show",
    "race": "Divine"
  },
  {
    "name": "Atropos",
    "url": "https://img.game8.co/3453851/a74fd78213596ddbec4824640a4329f9.jpeg/show",
    "race": "Femme"
  },
  {
    "name": "Cerberus",
    "url": "https://img.game8.co/3453884/5ee484531a168c2a4e2fb15e25a06e39.jpeg/show",
    "race": "Beast"
  },
  {
    "name": "Girimehkala",
    "url": "https://img.game8.co/3453405/506b4f59d9882c18f96c140526e162b2.jpeg/show",
    "race": "Vile"
  },
  {
    "name": "Nebiros",
    "url": "https://img.game8.co/3453391/8f692f4d09d04e4502e4cf86abb0e48c.jpeg/show",
    "race": "Fallen"
  },
  {
    "name": "Rangda",
    "url": "https://img.game8.co/3453967/307e006566667e1be3b2cb955f3022ec.jpeg/show",
    "race": "Femme"
  },
  {
    "name": "Yamata no Orochi",
    "url": "https://img.game8.co/3453978/9490144441ad0589fd96d9ef162f5049.jpeg/show",
    "race": "Snake"
  },
  {
    "name": "Angel",
    "url": "https://img.game8.co/3450197/e1936c4b75c025219302998ea6aee5d7.jpeg/show",
    "race": "Divine"
  },
  {
    "name": "Feng Huang",
    "url": "https://img.game8.co/3450230/4601c3b7314fb8ffc12c239a4be2e00e.jpeg/show",
    "race": "Avian"
  },
  {
    "name": "Futsunushi",
    "url": "https://img.game8.co/3453894/d97a88a41d833b103fd733359932deb8.jpeg/show",
    "race": "Wargod"
  },
  {
    "name": "Sraosha",
    "url": "https://img.game8.co/3453392/9c29b4fa564a8e3bb338d577e1eb03c7.jpeg/show",
    "race": "Herald"
  },
  {
    "name": "Xuanwu",
    "url": "https://img.game8.co/3450234/f311e2f195f114f8f20b85257d276963.jpeg/show",
    "race": "Dragon"
  },
  {
    "name": "Horus",
    "url": "https://img.game8.co/3450483/79ed87580c18e03460a61b12e8b50258.jpeg/show",
    "race": "Deity"
  },
  {
    "name": "Arahabaki",
    "url": "https://img.game8.co/3453860/6303bb6a0c7c453480c7977fe182c729.jpeg/show",
    "race": "Kunitsu"
  },
  {
    "name": "Silky",
    "url": "https://img.game8.co/3450469/2adabf0b938734c8f694f44c8c290157.jpeg/show",
    "race": "Fairy"
  },
  {
    "name": "Cu Chulainn",
    "url": "https://img.game8.co/3452904/addea4c0712b2347aa22357f4766b307.jpeg/show",
    "race": "Genma"
  },
  {
    "name": "Scathach",
    "url": "https://img.game8.co/3453249/0ebb88bf7a281ed92d93778dee0add12.jpeg/show",
    "race": "Megami"
  },
  {
    "name": "Garuda",
    "url": "https://img.game8.co/3453372/f86746308cfc72c63d3f2379217143c6.jpeg/show",
    "race": "Avian"
  },
  {
    "name": "Archangel",
    "url": "https://img.game8.co/3450222/39a65720091187e618d9fac4a45d6ccd.jpeg/show",
    "race": "Divine"
  },
  {
    "name": "Thor",
    "url": "https://img.game8.co/3453975/825703b6917711a27c2fe984cbc3d790.jpeg/show",
    "race": "Kishin"
  },
  {
    "name": "Narcissus",
    "url": "https://img.game8.co/3450455/4b8655604177d364ea00cc12de5820f7.jpeg/show",
    "race": "Jirae"
  },
  {
    "name": "Demeter",
    "url": "https://img.game8.co/3455556/03473e2c90b4860e121e4b1fe4c8a85c.jpeg/show",
    "race": "Megami"
  },
  {
    "name": "Shiisaa",
    "url": "https://img.game8.co/3450224/f6935ad8aee0267f3983534cc4807904.jpeg/show",
    "race": "Holy"
  },
  {
    "name": "Melchizedek",
    "url": "https://img.game8.co/3453329/d58658e20add03f900460441f795a025.jpeg/show",
    "race": "Herald"
  },
  {
    "name": "Alilat",
    "url": "https://img.game8.co/3453865/1604db810935cc7ea81fe28816bd2a8e.jpeg/show",
    "race": "Lady"
  },
  {
    "name": "Power",
    "url": "https://img.game8.co/3450467/98361d53f582e607843fd0b9d3fe5408.jpeg/show",
    "race": "Divine"
  },
  {
    "name": "Asura",
    "url": "https://img.game8.co/3455214/886525b0813f0fe7bee1d62625b5c23c.jpeg/show",
    "race": "Fury"
  },
  {
    "name": "Neko Shogun",
    "url": "https://img.game8.co/3450188/8a97aa217bd3240e19b2b52a25ca88f4.jpeg/show",
    "race": "Wargod"
  },
  {
    "name": "Hariti",
    "url": "https://img.game8.co/3450345/3c2aa895f44052a12ac349a548d33b8b.jpeg/show",
    "race": "Lady"
  },
  {
    "name": "Baihu",
    "url": "https://img.game8.co/3450482/f1ef8b9d84e8ea05e95bb4b6ea1e66d2.jpeg/show",
    "race": "Holy"
  },
  {
    "name": "Vishnu",
    "url": "https://img.game8.co/3453976/b496415a30f2768f7e6e42f1758a6b5e.jpeg/show",
    "race": "Deity"
  },
  {
    "name": "Fortuna",
    "url": "https://img.game8.co/3450212/f14f5b6b20479b2d31ad78e227557205.jpeg/show",
    "race": "Megami"
  },
  {
    "name": "Anubis",
    "url": "https://img.game8.co/3450464/ae8077c2aab6be97c020eb3913858c07.jpeg/show",
    "race": "Avatar"
  },
  {
    "name": "Flaemis",
    "url": "https://img.game8.co/3450221/d14b1e68e4d35c61eb9ad3f120cceb18.jpeg/show",
    "race": "Element"
  },
  {
    "name": "Apsaras",
    "url": "https://img.game8.co/3450214/16d7f2d33437fb66a98405d4130a8551.jpeg/show",
    "race": "Megami"
  },
  {
    "name": "Kushinada-Hime",
    "url": "https://img.game8.co/3450504/ad91b6e7b9b2d34763e9176da12c3691.jpeg/show",
    "race": "Kunitsu"
  },
  {
    "name": "Ananta",
    "url": "https://img.game8.co/3453863/9e697e60dde61d8dcf500099322c4a69.jpeg/show",
    "race": "Dragon"
  },
  {
    "name": "Bishamonten",
    "url": "https://img.game8.co/3453881/720d7f7728840e713156b2a2268e10cd.jpeg/show",
    "race": "Kishin"
  },
  {
    "name": "Thunderbird",
    "url": "https://img.game8.co/3450465/2aed4c9adf47b64d5c6e9993c90d5c93.jpeg/show",
    "race": "Avian"
  },
  {
    "name": "Seth",
    "url": "https://img.game8.co/3453969/91b4feea3727959319abb87d627cf71d.jpeg/show",
    "race": "Drake"
  },
  {
    "name": "Attis",
    "url": "https://img.game8.co/3450254/2ac6c3122613b191b4f0ce9136705e4d.jpeg/show",
    "race": "Kishin"
  },
  {
    "name": "Inanna",
    "url": "https://img.game8.co/3455558/6d732d793530826f5e183b8c1f4e5d06.jpeg/show",
    "race": "Lady"
  },
  {
    "name": "Jikokuten",
    "url": "https://img.game8.co/3453164/7cfb6c15068c8f7811486a0db1b302c0.jpeg/show",
    "race": "Kishin"
  },
  {
    "name": "Ame-no-Uzume",
    "url": "https://img.game8.co/3450232/53191d995f25a9c545b0561309269dc4.jpeg/show",
    "race": "Megami"
  },
  {
    "name": "Makami",
    "url": "https://img.game8.co/3450228/a12276eadbd4a5e864340e596f6dccff.jpeg/show",
    "race": "Avatar"
  },
  {
    "name": "Mithra",
    "url": "https://img.game8.co/3453389/20fa15b29345c345334221ac2b3ef00a.jpeg/show",
    "race": "Deity"
  },
  {
    "name": "Skadi",
    "url": "https://img.game8.co/3453971/26322803481e418440f13604664caee1.jpeg/show",
    "race": "Lady"
  },
  {
    "name": "Siegfried",
    "url": "https://img.game8.co/3453318/0b222f16387194a609683920bfd34aa7.jpeg/show",
    "race": "Wargod"
  },
  {
    "name": "Chernobog",
    "url": "https://img.game8.co/3453163/75d6f23e60163a18447ae6f76fd060b0.jpeg/show",
    "race": "Fury"
  },
  {
    "name": "Dionysus",
    "url": "https://img.game8.co/3450486/8875320629173fe61b589b58388bb0bf.jpeg/show",
    "race": "Fury"
  },
  {
    "name": "Zouchouten",
    "url": "https://img.game8.co/3450341/dad7802c59e85a7dac7ea2f2ca2818d3.jpeg/show",
    "race": "Kishin"
  },
  {
    "name": "Lakshmi",
    "url": "https://img.game8.co/3453441/d98af367b9cc63485f6ce7c7d4488d6e.jpeg/show",
    "race": "Megami"
  },
  {
    "name": "Ganesha",
    "url": "https://img.game8.co/3453253/8dd07a2fbc62fcefcfe356e427711702.jpeg/show",
    "race": "Wargod"
  },
  {
    "name": "Dominion",
    "url": "https://img.game8.co/3452903/c476d1e8aa715c1657ccc5f3c2877455.jpeg/show",
    "race": "Divine"
  },
  {
    "name": "Sandalphon",
    "url": "https://img.game8.co/3453403/d9fc1fce9eb946012c47cb43ac02d597.jpeg/show",
    "race": "Herald"
  },
  {
    "name": "Take-Minakata",
    "url": "https://img.game8.co/3450223/2d0282c9604df4605223a0f19946c7e3.jpeg/show",
    "race": "Kunitsu"
  },
  {
    "name": "Zhu Que",
    "url": "https://img.game8.co/3450481/493890f61ed0bab8ad43d76c213c7166.jpeg/show",
    "race": "Avian"
  },
  {
    "name": "Atavaka",
    "url": "https://img.game8.co/3452901/adb990bd380c2c72f474b7f7af24dd1a.jpeg/show",
    "race": "Deity"
  },
  {
    "name": "Isis",
    "url": "https://img.game8.co/3450492/61601bf7a4878b2d24ef758f495400d5.jpeg/show",
    "race": "Lady"
  },
  {
    "name": "Principality",
    "url": "https://img.game8.co/3450257/c2695d7445e2ce6f3f4c3a6906f5f8af.jpeg/show",
    "race": "Divine"
  },
  {
    "name": "Cybele",
    "url": "https://img.game8.co/3453886/948702e6427b79afa04c4440d6f42e84.jpeg/show",
    "race": "Lady"
  },
  {
    "name": "Lilith",
    "url": "https://img.game8.co/3453954/a915d99673487d50bc62888aac97d6b9.jpeg/show",
    "race": "Night"
  },
  {
    "name": "Parvati",
    "url": "https://img.game8.co/3450338/718447126a7a0d48e869fd0e2b96730c.jpeg/show",
    "race": "Megami"
  },
  {
    "name": "Sarasvati",
    "url": "https://img.game8.co/3450507/6e36ae7c7bebc8b44a937de41be8355c.jpeg/show",
    "race": "Megami"
  },
  {
    "name": "Jatayu",
    "url": "https://img.game8.co/3450291/e35865442d7f830a1d2d7e8dca3769ef.jpeg/show",
    "race": "Avian"
  },
  {
    "name": "Barong",
    "url": "https://img.game8.co/3453338/bb1eea8f7dca88232e50f7422212bb01.jpeg/show",
    "race": "Avatar"
  },
  {
    "name": "Leanan Sidhe",
    "url": "https://img.game8.co/3450217/0499191e9ac39908c3ced63922340258.jpeg/show",
    "race": "Femme"
  },
  {
    "name": "Zaou-Gongen",
    "url": "https://img.game8.co/3455559/48c2d7cb6a0f185b2c970b82c6d7262e.jpeg/show",
    "race": "Fury"
  },
  {
    "name": "Belphegor",
    "url": "https://img.game8.co/3453849/f498371906bf5795523835e55b21d559.jpeg/show",
    "race": "Tyrant"
  },
  {
    "name": "Kikuri-Hime",
    "url": "https://img.game8.co/3450236/90cecf9b6476e97ed5fd762f9ce4e79d.jpeg/show",
    "race": "Lady"
  },
  {
    "name": "Mot",
    "url": "https://img.game8.co/3453311/a38910d2c11a4154a62e24b5d9794c82.jpeg/show",
    "race": "Fury"
  },
  {
    "name": "Thoth",
    "url": "https://img.game8.co/3450293/aabf4f0471eb18d618913d678ebd233d.jpeg/show",
    "race": "Deity"
  },
  {
    "name": "Abaddon",
    "url": "https://img.game8.co/3453858/bc369a8704036c0d793c94f0cacd9982.jpeg/show",
    "race": "Tyrant"
  },
  {
    "name": "Camael",
    "url": "https://img.game8.co/3453883/0cfa59027269224b3f91f1e5168284ac.jpeg/show",
    "race": "Herald"
  },
  {
    "name": "Yatagarasu",
    "url": "https://img.game8.co/3453073/41ceefd3caa2aba4b0b041870549a416.jpeg/show",
    "race": "Avian"
  },
  {
    "name": "Quetzalcoatl",
    "url": "https://img.game8.co/3450347/db0b4974a423250932de6a3fb2e49d3c.jpeg/show",
    "race": "Dragon"
  },
  {
    "name": "Yoshitsune",
    "url": "https://img.game8.co/3450532/1fef5e9897b7c00b3645ec2e7663cc92.jpeg/show",
    "race": "Wargod"
  },
  {
    "name": "Chimera",
    "url": "https://img.game8.co/3453220/c57293ea162b5e3fe5654dbd4d64df72.jpeg/show",
    "race": "Holy"
  },
  {
    "name": "Loki",
    "url": "https://img.game8.co/3453340/7d347252b21096e6e251905cc12f806c.jpeg/show",
    "race": "Tyrant"
  },
  {
    "name": "Aeros",
    "url": "https://img.game8.co/3450203/d7b71750452abbc5249f447f4ca316eb.jpeg/show",
    "race": "Element"
  },
  {
    "name": "Koumokuten",
    "url": "https://img.game8.co/3450485/d60f71e1211abbc5cae0081b305b2074.jpeg/show",
    "race": "Kishin"
  },
  {
    "name": "Ouyamatsumi",
    "url": "https://img.game8.co/3455217/f7d015aa2462e36a50dcf81a6d9cc411.jpeg/show",
    "race": "Kunitsu"
  },
  {
    "name": "Amon",
    "url": "https://img.game8.co/3455210/e1b8f0bd0141694b1a68536284671ff9.jpeg/show",
    "race": "Tyrant"
  },
  {
    "name": "Qing Long",
    "url": "https://img.game8.co/3450491/a224d9c0030032302d694f174d53a0f4.jpeg/show",
    "race": "Dragon"
  },
  {
    "name": "Okuninushi",
    "url": "https://img.game8.co/3455488/2acc2f4344680f7ba9dc9647c8414298.jpeg/show",
    "race": "Kunitsu"
  },
  {
    "name": "Maria",
    "url": "https://img.game8.co/3455208/d15dbcd573aee867edf24542aa804843.jpeg/show",
    "race": "Megami"
  },
  {
    "name": "Mara",
    "url": "https://img.game8.co/3453382/bc49f35e5af80dd8a45926d34f8a57af.jpeg/show",
    "race": "Tyrant"
  },
  {
    "name": "Belial",
    "url": "https://img.game8.co/3455553/5affd32325562a5c535f72dc497a10b4.jpeg/show",
    "race": "Tyrant"
  },
  {
    "name": "Metatron",
    "url": "https://img.game8.co/3455206/d676b311a1837d0df8033c62a32cafc6.jpeg/show",
    "race": "Herald"
  },
  {
    "name": "Aquans",
    "url": "https://img.game8.co/3450211/8ec97ccb4d4414b6c48c319232ed0cab.jpeg/show",
    "race": "Element"
  }
]

async function download(command) {
    return new Promise((resolve, reject) => {
        exec(command, (error, stdout, stderr) => {
            if (error) {
                console.log(error);
                reject();
                return;
            }
            resolve();
        });
    });
}

async function main() {
    for (let i = 0; i < images.length; i++) {
        const image = images[i];
        const str = `wget -O "${image.name}.jpeg" ${image.url}`;
        console.log(str);
        await download(str);
        // exec(`wget 0`)
    }
}

main();
