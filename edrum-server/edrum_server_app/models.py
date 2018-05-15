from django.db import models

# Create your models here.
class NoteFileModel(models.Model):
    id = models.AutoField(primary_key = True)
    title = models.TextField(default='')
    file = models.FileField(null=True)
    uploaded_at = models.DateTimeField(auto_now_add=True)

    class Meta:
        ordering = ('id',)