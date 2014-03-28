/* main.c - main */

#include <xinu.h>
#include <stdio.h>
#include <string.h>
/************************************************************************/
/* */
/* main - main program for testing Xinu */
/* */
/************************************************************************/
char wordsbs[7500] = "WEST LAFAYETTE, Ind. - President Mitch Daniels began a new series of governance reports to the Purdue Board of Trustees on Friday (Feb. 21) with a look at institutional excellence. The report was the first of a series that will focus each meeting on one of the five areas of accountability chosen by the board and around which the president's contract is based. In April, the president will discuss fundraising; in May, he will discuss affordability, efficiency and student debt; in September, he will discuss student intellectual growth and achievement; and in December, he will discuss student success. In addition to Daniels' report, each meeting will feature updates on initiatives that are part of Purdue Moves and a report from an academic area. In Fridays report, Daniels previewed some preliminary themes recommended by a faculty committee on institutional excellence, including faculty members' recent awards and honors, their entrepreneurial activities and research productivity; and trends in admissions, including the percentage of top high school students who choose to attend Purdue. The number of Purdue faculty members who have received notable awards is encouraging, Daniels said. For example, more than 100 have won major early-career awards, and of those, 20 received their awards during 2013-14. In addition, 66 Purdue faculty members are fellows of the American Association for the Advancement of Science, 12 of whom received the honor this academic year. Faculty members' entrepreneurial activities also should be noted, Daniels said. For example, so far this fiscal year, faculty members have submitted 223 patent applications. The number of patent applications has increased steadily during the past six months. Another indicator is the value of faculty members' research awards. So far this fiscal year, faculty members have received about $231 million in research awards. That approaches the value of awards received between the same periods in fiscal year 2011 - the most lucrative year in the past 10. In the area of admissions, applications to Purdue have increased overall by 31 percent over last year. Some of that increase can be attributed to Purdue's recent acceptance of a nationwide common application. Specifically, domestic, out-of-state applications have increased 52 percent, which Daniels said is a rough indicator of Purdue's rising national reputation. Additionally, the number of resident and nonresident students who scored in the top 5 percent on the ACT or SAT has increased. Since fall 2009, that number as a percentage of the freshman class has risen more than 10 percentage points, to 31.5 percent. Presenting to trustees about Purdue's focus on investing in drug discovery were Philip Low, the Ralph C. Corley Distinguished Professor of Chemistry, and Timothy Ratliff, professor of comparative pathobiology and the Robert Wallace Miller Director of the Center for Cancer Research. Presenting about advancing plant science research were Jay Akridge, the Glenn W. Sample Dean of Purdue Agriculture, and Karen Plaut, senior associate dean for research and faculty affairs in the College of Agriculture. By investing in drug discovery, Purdue's researchers will be able to accelerate the rate at which they can move their work from the lab to commercialization and on to those who need it most, Low and Ratliff said. By advancing plant science research, Akridge and Plaut said Purdue's scientists will lead the world in translating their research to commercially important crops and eventually moving products through a pipeline for commercialization. For more information about these and other Purdue Moves, visit the initiatives' website. WEST LAFAYETTE, Ind. - The Purdue Board of Trustees on Friday (Feb. 21) approved naming the School of Civil Engineering for the Lyles family in recognition of a $15 million gift from the Lyles Foundation. The school will be known as the Lyles School of Civil Engineering. The gift will be used to broaden the school's capacities for learning and discovery and for generating solutions to critical global problems. \"The Lyles family has deep ties to Purdue and a long history of generous support for the university,\" said President Mitch Daniels. \"This latest of so many gifts fits uniquely into the university's action plan to increase the number of engineers we supply to our state and nation.\" In a statement, brothers Bill and Gerald Lyles said: \"We believe that a reinvigoration of the science, technology, engineering and math (STEM) disciplines is critical for our society. We are so proud of Purdue for taking the lead in STEM education in the United States. We are delighted that Purdue is expanding all aspects of its highly regarded programs to meet the national challenge to educate future engineers.\" They also noted that the School of Civil Engineering has been an integral part of their family and the industry in which they are involved. \"With proven abilities in experimental and computational techniques and our understanding of new and aging infrastructure, the School of Civil Engineering is addressing the grand challenges facing natural and built environments around the world,\" said Rao S. Govindaraju, the Bowen Engineering Head of Civil Engineering. \"The Lyles gift will enable us to amplify our impact through enhanced student learning and faculty research resulting in solutions that will lead to more sustainable and more resilient societies.\" The Lyles family construction business was started in central California in 1945 by Bill and Gerald's parents, William Jr. and Elizabeth Lyles. It has since grown into one of the larger California contractors, specializing in water and other infrastructure. Under their direction, Bill and Gerald Lyles have expanded the enterprise into real estate development, real estate rentals and agriculture. They credit their Purdue civil engineering education for much of their success. Bill Lyles received his bachelor's degree in civil engineering in 1955. Gerald Lyles received his bachelor's degree in civil engineering in 1964 and also earned a master's in industrial administration from Krannert School of Management in 1971. Bill's son, Will Lyles, earned bachelor's degrees in civil engineering and economics from Purdue in 1981. Other members of the Lyles family are Purdue alumni, including William Jr., who earned a bachelor's in civil engineering in 1935; Bill and Gerald's mother, Elizabeth, who earned a bachelor's degree in science in 1933 and a master's degree in education in 1934; and Bill and Gerald's sister Marybeth Lyles-Porter Seay, who earned a bachelor's degree in speech, language and hearing sciences in 1959. Their maternal grandfather, Henry Gerald Venemann, was a professor in the School of Mechanical Engineering. The family previously contributed to the Lyles Family Ideas to Innovation Learning Laboratory (i2i) in the School of Civil Engineering. In 1992 their mother funded the William M. Lyles Computational Laboratory, used by the School of Civil Engineering and the Division of Construction Engineering and Management. Lyles-Porter Hall, now under construction, is named in honor of a $10 million 2009 gift from Marybeth Lyles-Porter Seay. The new building will house the Department of Speech, Language and Hearing Sciences, the Indiana University School of Medicine-Lafayette and other health programs.";
int sem;
pipid32 wrpid1, repid1;
void writer(pipid32 pip, int len, char c, int s) {
int tlen = strnlen(wordsbs, 8000);
kprintf("Check1\r\n");
if (SYSERR == pipwrite(pip, wordsbs, tlen)) {
kprintf("Write %c: Fail to write into pip!\r\n", c);
}
kprintf("Check2\r\n");
sleep(2);

tlen = 2000;
int length = 0;
kprintf("Check3\r\n");
while (length < tlen) {
int mylen = pipwrite(pip, &wordsbs[length], 100);
kprintf("Check4\r\n");
if (SYSERR == mylen) {
kprintf("Writer %c: Fail to write into the pip\r\n", c);
break;
} else {
wait(sem);
kprintf("Writer %c: write %d bytes to pip total=%d\r\n", c, mylen, length);
signal(sem);
}
length += mylen;
sleepms(s);
}
sleep(3);
wait(sem);
if (SYSERR == pipdisconnect(pip)) {
kprintf("Writer %c: Fail to disconnect the pip!\r\n", c);
}else {
kprintf("Writer %c: disconnect the pip successfully\r\n", c);
}
if (SYSERR == pipdelete(pip)) {
kprintf("Writer %c: Fail to delete the pip!\r\n", c);
}else {
kprintf("Writer %c: delete the pip successfully\r\n", c);
}

if(c=='b') {
if(SYSERR == pipconnect(pip, wrpid1, repid1)) {
kprintf("Fail: fail to reconnect pip!\r\n");

} else {
kprintf("Pass: reconnect pip!\r\n");
}
}
signal(sem);
return;
}
void reader(pipid32 pip, int len, char c, int s) {
// kprintf("[Rd]: rd %d chars\r\n", len);
int length = 0;
char mybuf[7500];
int mylen;
int success = 1;
int tlen = strnlen(wordsbs, 8000);
while (length < tlen) {
mylen = pipread(pip, &mybuf[length], tlen-length);
if (SYSERR == mylen) {
kprintf("Reader %c: Fail to read from the pip\r\n", c);
success = 0;
break;
} else {
kprintf("Reader %c: read %d bytes from pip\r\n", c, mylen);
kprintf("Reader: Check1, %d\r\n",tlen);
}
length += mylen;
sleepms(s);
}
if( success ) {
kprintf("Reader %c finish characters reading!\r\n");
int flag = 1;
int i = 0;
while( i < tlen) {
if(mybuf[i] != wordsbs[i]) {
flag = 0;
break;
}
i++;
}
if(flag) {
kprintf("Pass reader %c: read the right characters!\n\r", c);
} else {
kprintf("Fail reader %c: read wrong characters!\n\r", c);
}
} else {

wait(sem);
if (SYSERR == pipdisconnect(pip)) {
kprintf("Reader %c: Fail to disconnect the pip!\r\n", c);
} else {
kprintf("Reader %c: disconnect the pip successfully!\r\n", c);
} 
signal(sem);

return;
}

kprintf("Second round of test for read & write.\r\n");
length = 0;
tlen = 2000;
while (length < tlen) {
mylen = pipread(pip, &mybuf[length], 1000);
if (SYSERR == mylen) {
kprintf("Reader %c: Fail to read from the pip\r\n", c);
break;
} else {
wait(sem);
kprintf("Reader %c: read %d bytes from pip total=%d\r\n", c, mylen, length);
signal(sem);
}
length += mylen;
}
wait(sem);
if (SYSERR == pipdisconnect(pip)) {
kprintf("Reader %c: Fail to disconnect the pip!\r\n", c);
} else {
kprintf("Reader %c: disconnect the pip successfully!\r\n", c);
}
signal(sem);
return;
}

int main(int argc, char **argv) {
sem = semcreate(1);
pipid32 pip[11];
kprintf("---------------Test #1: pip create------------------\r\n");
int i;
for(i=0; i<11; i++) {
pip[i] = pipcreate();
if(pip[i] == SYSERR) {
kprintf("Fail to create the %dth pip!\r\n", i+1);
if(i==0) {
return 0;
}
}
}

kprintf("-------------Test #2: pip connect-----------------\r\n");
pipid32 ivpip = 100;
pid32 wrpid2, wrpid3;
pid32 repid2, repid3;
pid32 ivpid = 100;
wrpid1 = create(writer, 2048, 20, "writer1", 4, pip[0], 1000, 'a', 0);
repid1 = create(reader, 2048, 20, "reader1", 4, pip[0], 1000, 'a', 100);
wrpid2 = create(writer, 2048, 20, "writer2", 4, pip[1], 1000, 'b', 100);
repid2 = create(reader, 9000, 20, "reader2", 4, pip[1], 1000, 'b', 100);
if (SYSERR == pipconnect(ivpip, wrpid1, repid1)) {
kprintf("Pass: fail to connect invalid pip!\r\n");
} else {
kprintf("Fail: connect to invalid pip!\r\n");
}
if (SYSERR == pipconnect(pip[0], wrpid1, ivpid)) {
kprintf("Pass: fail to connect invalid process!\r\n");
} else {
kprintf("Fail: connect to invalid process!\r\n");
}
if (SYSERR == pipconnect(pip[1], wrpid2, repid2)) {
kprintf("Fail: fail to connect valid pip!\r\n");
return 0;
} else {
kprintf("Pass: connect to valid pip!\r\n");
}
if (SYSERR == pipconnect(pip[1], wrpid1, repid1)) {
kprintf("Pass: fail to connect a pip twice!\r\n");
} else {
kprintf("Fail: connect to a pip twice!\r\n");
}
kprintf("-----------------------Test #3: Pip read & write & delete & disconnect -----------------\r\n");

wrpid3 = create(writer, 2048, 20, "writer3", 4, pip[1], 1000, 'c', 0);
repid3 = create(reader, 2048, 20, "reader3", 4, pip[1], 1000, 'c', 100);

resume(wrpid3);
resume(repid3);
// sleep(2);
// resume(wrpid2);
// resume(repid2);

while(1) {
sleep(100);
}
return OK;
}

