var cooleArray = [
	[5, 39],    // 0
	[6, 309],   // 1
	[7, 123],   // 2
	[8, 48],    // 3
	[9, 290],   // 4
	[10, 59],   // 5
	[11, 209],  // 6
	[12, 1030], // 7
	[13, 199],  // 8
	[14, 135],  // 9
	[15, 136],  // 10
	[16, 149],  // 11
	[17, 104],  // 12
	[18, 147],  // 13
	[19, 162],  // 14
	[20, 116],  // 15
]

//                                 vvv pointer in cpp?
function BinarySearch(searchValue, array, range) {
	if(!range) range=[0, array.length-1];

	var midpoint = Math.round((range[0] + range[1]) / 2);

	if(array[midpoint][0] == searchValue) return midpoint;
	range[searchValue < array[midpoint][0] ? 1 : 0] = midpoint;

	return BinarySearch(searchValue, array, range);
}

// var index = BinarySearch(16, cooleArray);
// console.log(index);
// console.log(cooleArray[index]);



























var cooleDriehoek = [
	[10, 0],
	[50, 100],
	[0, 70]
]

var laagsteY = cooleDriehoek[0][1];
var hoogsteY = cooleDriehoek[0][1];

var zijdeBegin = 0;
var zijdeEinde = 0;

for (var i = 0; i < 3; i++) {
	hoogsteY = Math.max(hoogsteY, cooleDriehoek[i][1]);
	laagsteY = Math.min(laagsteY, cooleDriehoek[i][1]);
}

for (var i = 0; i < 3; i++) {
	if (cooleDriehoek[i][1] == hoogsteY) zijdeBegin = i;
	if (cooleDriehoek[i][1] == laagsteY) zijdeEinde = i;
}

console.log(`De langste zijde is van index ${zijdeBegin} tot ${zijdeEinde} (${laagsteY}-${hoogsteY})`);
