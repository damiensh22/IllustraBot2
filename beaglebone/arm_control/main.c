/**
 * arm_control server
 *********************************************************************
 * Fablab Lannion IllustraBot2 project
 * http://fablab-lannion.org/wiki/index.php?title=IllustraBot2
 *********************************************************************
 * Copyright: (c) 2013 Jérôme Labidurie
 * Licence:   GNU General Public Licence version 3
 * Email:     jerome.labidurie at gmail.com
 *********************************************************************
 * This file is part of IllustraBot2.
 * 
 * IllustraBot2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * IllustraBot2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with IllustraBot2.  If not, see <http://www.gnu.org/licenses/>.
 *********************************************************************
 */

#include <msock.h>
#include <proto.h>

void dump_message (message_t* msg)
{
   printf ("received message:\n");
   printf (" ver:%d, size:%d, type:%d\n", msg->version, msg->size, msg->type);
   switch (msg->type) {
      case T_DATA_WII:
         printf (" b1:%d, b2:%d\n", msg->pl.nunchuk.b1, msg->pl.nunchuk.b2);
         printf (" x:%3.3f, y:%3.3f, z:%3.3f\n", msg->pl.nunchuk.x, msg->pl.nunchuk.y, msg->pl.nunchuk.z);
         break;
      case T_DATA_JOY:
         printf (" b1:%d, b2:%d, b3:%d, b4:%d\n",
                 msg->pl.joystick.b1, msg->pl.joystick.b2, msg->pl.joystick.b3, msg->pl.joystick.b4);
         printf (" x1:%6d, y1:%6d, x2:%6d, y2:%6d,\n",
                 msg->pl.joystick.x1, msg->pl.joystick.y1, msg->pl.joystick.x2, msg->pl.joystick.y2);
         break;
      case T_COMMAND:
         printf (" command: %s\n",msg->pl.txt);
         break;
      default:
         printf ("unknown message type:%d\n",msg->type);
         break;
   }
} // dump_message

int main (int argc,char **argv) 
{
   int
   connected,
   rc,
   client_port,
   port,
   sock_fd;
   
   char
   szclient_host[64],
   szclient_ip[64],
   szbuf[BUFSIZ];
   
   if (argc < 2)
   {
      (void) fprintf(stderr,"usage: %s port\n",argv[0]);
      return(1);
   }
   port=atoi(argv[1]);
   
   /* open socket and start listening */
   sock_fd=ServerSocket((u_short) port,5);
   if (sock_fd == -1)
   {
      (void) fprintf(stderr,"Failed to open socket\n");
      return (1);
   }
   
   /* we will be here only when a client connects */
   
   /* get client informations */
   rc=getPeerInfo(sock_fd,szclient_host,szclient_ip,(u_short*)&client_port);
   if (rc == 0)
   {
      (void) fprintf(stderr,"================================\n");
      (void) fprintf(stderr,"Client hostname %s\n",szclient_host);
      (void) fprintf(stderr,"Client IP: %s\n",szclient_ip);
      (void) fprintf(stderr,"Client port: %d\n",client_port);
      (void) fprintf(stderr,"================================\n");
   }
   
   connected=1;
   /* server the client */
   while (connected)
   {
      //         rc=sockGets(sock_fd,szbuf,sizeof(szbuf));
      rc = sockRead (sock_fd, szbuf, HEADER_SIZE);
      if (rc < 0)
         break;
      if (rc)
      {
         //            printf("ver:%d, size:%d, type:%d\n", szbuf[0], szbuf[1], szbuf[2]);
         printf ("read %d (exp:%d), still %d bytes to read\n",rc, (int)HEADER_SIZE, (int)(szbuf[1]-HEADER_SIZE));
         rc = sockRead (sock_fd, szbuf+HEADER_SIZE, szbuf[1] - HEADER_SIZE);
         if (rc) {
            dump_message( (message_t*) szbuf);
         }
      }
      //send back answer
      (void) sockPuts(sock_fd,"OK\n");
   }
   
   
   (void) fprintf(stderr," <closed>\n\n");
   close(sock_fd);
   return(0);
}