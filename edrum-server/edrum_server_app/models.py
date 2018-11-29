from django.db import models

# Create your models here.
class NoteFileModel(models.Model):
    server_id = models.AutoField(primary_key = True)
    name = models.CharField(max_length=50,default='')
    artist = models.CharField(max_length=50,default='')
    date = models.DateField(auto_now=False,auto_now_add=True)
    ID = models.CharField(max_length=20,default='')
    song = models.FileField(null=True)

    class Meta:
        ordering = ('server_id',)
