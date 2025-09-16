const normalize = (str:string) => {
    return str.toLowerCase().split("").sort().join();
}

export const isAnaragram = (str1:string, str2:string) => {

    if (str1.length != str2.length) return false;

    return normalize(str1) == normalize(str2);

}

//[1,1,1,2,2,3]

export const toKFrequent = (nums:number[], k:number) => {

    let freq: Record<number, number> = {};

    //Count the frequencies
    for(const num of nums){
        freq[num] = (freq[num] || 0) + 1;
    }

    const entries = Object.entries(freq);

    console.log("entries: ", entries);

    const sorted = entries.sort((a, b) => b[1] - a[1]);

    console.log("sorted: ", sorted);

    const sliced = sorted.slice(0, k);

    console.log("sliced: ", sliced);

    const mapped = sliced.map((row) => {
        //console.log(row[0]);
        //console.log(row[1]);
        return Number(row[0]);
    })

    console.log("mapped: ", mapped);

    return mapped;
}

interface UserProfile {
    id: number; 
    name: string; 
    age: number
}

type UserProfileArray = UserProfile[];

function groupByAge(users: UserProfileArray) {
  return users.reduce((acc: Record<number, UserProfileArray>, user) => {
    if (!acc[user.age]) {
      acc[user.age] = [];
    }
    acc[user.age].push(user);
    return acc;
  }, {});
}

console.log(groupByAge([
  { id: 1, name: "Alice", age: 25 },
  { id: 2, name: "Bob", age: 30 },
  { id: 3, name: "Charlie", age: 25 }
]));

export interface RequestItem {
    ref:string;
    name:string;
}

export type RequestItemArray = RequestItem[];

export const groupItemsByRef = (items:RequestItemArray) => {

    const grouppedItems = items.reduce((acc:Record<string, RequestItemArray>, item:RequestItem) => {

        if(!acc[item.ref]){
            acc[item.ref] = [];
        }

        acc[item.ref].push(item);

        return acc;
    }, {})

    return grouppedItems;
}
